// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2006 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/mld6igmp/mld6igmp_vif.cc,v 1.51 2006/06/06 23:09:04 pavlin Exp $"


//
// MLD6IGMP virtual interfaces implementation.
//


#include "mld6igmp_module.h"
#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"
#include "libxorp/ipvx.hh"

#include "mrt/inet_cksum.h"

#include "mld6igmp_vif.hh"


//
// Exported variables
//

//
// Local constants definitions
//

//
// Local structures/classes, typedefs and macros
//

//
// Local variables
//

//
// Local functions prototypes
//


/**
 * Mld6igmpVif::Mld6igmpVif:
 * @mld6igmp_node: The MLD6IGMP node this interface belongs to.
 * @vif: The generic Vif interface that contains various information.
 * 
 * MLD6IGMP protocol vif constructor.
 **/
Mld6igmpVif::Mld6igmpVif(Mld6igmpNode& mld6igmp_node, const Vif& vif)
    : ProtoUnit(mld6igmp_node.family(), mld6igmp_node.module_id()),
      Vif(vif),
      _mld6igmp_node(mld6igmp_node),
      _primary_addr(IPvX::ZERO(mld6igmp_node.family())),
      _querier_addr(IPvX::ZERO(mld6igmp_node.family())),
      _ip_router_alert_option_check(false),
      _query_interval(TimeVal(0, 0)),
      _query_last_member_interval(TimeVal(0, 0)),
      _query_response_interval(TimeVal(0, 0)),
      _robust_count(0),
      _dummy_flag(false)
{
    XLOG_ASSERT(proto_is_igmp() || proto_is_mld6());
    
    //
    // TODO: when more things become classes, most of this init should go away
    //
    _buffer_send = BUFFER_MALLOC(BUF_SIZE_DEFAULT);
    _proto_flags = 0;
    _startup_query_count = 0;

    //
    // Set the protocol version
    //
#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp()) {
	set_proto_version_default(IGMP_VERSION_DEFAULT);
	_query_interval.set(TimeVal(IGMP_QUERY_INTERVAL, 0));
	_query_last_member_interval.set(
	    TimeVal(IGMP_LAST_MEMBER_QUERY_INTERVAL, 0));
	_query_response_interval.set(TimeVal(IGMP_QUERY_RESPONSE_INTERVAL, 0));
	_robust_count = IGMP_ROBUSTNESS_VARIABLE;
    }
#endif // HAVE_IPV4_MULTICAST_ROUTING

#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6()) {
	set_proto_version_default(MLD_VERSION_DEFAULT);
	_query_interval.set(TimeVal(MLD_QUERY_INTERVAL, 0));
	_query_last_member_interval.set(
	    TimeVal(MLD_LAST_LISTENER_QUERY_INTERVAL, 0));
	_query_response_interval.set(TimeVal(MLD_QUERY_RESPONSE_INTERVAL, 0));
	_robust_count = MLD_ROBUSTNESS_VARIABLE;
    }
#endif // HAVE_IPV6_MULTICAST_ROUTING

    set_proto_version(proto_version_default());
}

/**
 * Mld6igmpVif::~Mld6igmpVif:
 * @: 
 * 
 * MLD6IGMP protocol vif destructor.
 * 
 **/
Mld6igmpVif::~Mld6igmpVif()
{
    string error_msg;

    stop(error_msg);
    
    // Remove all members entries
    map<IPvX, Mld6igmpGroupRecord *>::iterator iter;
    for (iter = _members.begin(); iter != _members.end(); ++iter) {
	Mld6igmpGroupRecord *group_record = iter->second;
	join_prune_notify_routing(IPvX::ZERO(family()),
				  group_record->group(), ACTION_PRUNE);
	delete group_record;
    }
    _members.clear();
    
    BUFFER_FREE(_buffer_send);
}

/**
 * Mld6igmpVif::set_proto_version:
 * @proto_version: The protocol version to set.
 * 
 * Set protocol version.
 * 
 * Return value: %XORP_OK is @proto_version is valid, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::set_proto_version(int proto_version)
{
#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp()) {
	if ((proto_version < IGMP_VERSION_MIN)
	    || (proto_version > IGMP_VERSION_MAX))
	return (XORP_ERROR);
    }
#endif // HAVE_IPV4_MULTICAST_ROUTING
    
#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6()) {
	if ((proto_version < MLD_VERSION_MIN)
	    || (proto_version > MLD_VERSION_MAX))
	return (XORP_ERROR);
    }
#endif // HAVE_IPV6_MULTICAST_ROUTING
    
    ProtoUnit::set_proto_version(proto_version);
    
    return (XORP_OK);
}

/**
 * Mld6igmpVif::proto_is_ssm:
 * @: 
 * 
 * Test if the interface is running a source-specific multicast capable
 * protocol version (e.g. IGMPv3 or MLDv2).
 * 
 * Return value: @true if the protocol version is source-specific multicast
 * capable, otherwise @fa.se
 **/
bool
Mld6igmpVif::proto_is_ssm() const
{
    if (proto_is_igmp())
	return (proto_version() >= IGMP_V3);
    if (proto_is_mld6())
	return (proto_version() >= MLD_V2);
    
    return (false);
}

/**
 * Mld6igmpVif::start:
 * @error_msg: The error message (if error).
 * 
 * Start MLD or IGMP on a single virtual interface.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::start(string& error_msg)
{
    string dummy_error_msg;

    if (! is_enabled())
	return (XORP_OK);

    if (is_up() || is_pending_up())
	return (XORP_OK);

    if (! is_underlying_vif_up()) {
	error_msg = "underlying vif is not UP";
	return (XORP_ERROR);
    }

    //
    // Start the vif only if it is of the appropriate type:
    // multicast-capable (loopback excluded).
    //
    if (! (is_multicast_capable() && (! is_loopback()))) {
	error_msg = "the interface is not multicast capable";
	return (XORP_ERROR);
    }

    if (update_primary_address(error_msg) < 0)
	return (XORP_ERROR);

    if (ProtoUnit::start() < 0) {
	error_msg = "internal error";
	return (XORP_ERROR);
    }

    // On startup, assume I am the MLD6IGMP Querier
    set_querier_addr(primary_addr());
    set_i_am_querier(true);
    
    //
    // Start the vif with the kernel
    //
    if (mld6igmp_node().start_protocol_kernel_vif(vif_index()) != XORP_OK) {
	error_msg = c_format("cannot start protocol vif %s with the kernel",
			     name().c_str());
	return (XORP_ERROR);
    }
    
    //
    // Join the appropriate multicast groups: ALL-SYSTEMS, ALL-ROUTERS,
    // and SSM-ROUTERS.
    //
    list<IPvX> groups;
    list<IPvX>::iterator groups_iter;
    groups.push_back(IPvX::MULTICAST_ALL_SYSTEMS(family()));
    groups.push_back(IPvX::MULTICAST_ALL_ROUTERS(family()));
    groups.push_back(IPvX::SSM_ROUTERS(family()));
    for (groups_iter = groups.begin();
	 groups_iter != groups.end();
	 ++groups_iter) {
	const IPvX& group = *groups_iter;
	if (mld6igmp_node().join_multicast_group(vif_index(), group)
	    != XORP_OK) {
	    error_msg = c_format("cannot join group %s on vif %s",
				 cstring(group), name().c_str());
	    return (XORP_ERROR);
	}
    }
    
    //
    // Query all members on startup
    //
    uint32_t timer_scale = mld6igmp_constant_timer_scale();
    TimeVal scaled_max_resp_time =
	(query_response_interval().get() * timer_scale);
    mld6igmp_send(primary_addr(),
		  IPvX::MULTICAST_ALL_SYSTEMS(family()),
		  mld6igmp_constant_membership_query(),
		  is_igmpv1_mode() ? 0 : scaled_max_resp_time.sec(),
		  IPvX::ZERO(family()),
		  dummy_error_msg);
    _startup_query_count = robust_count().get();
    if (_startup_query_count > 0)
	_startup_query_count--;
    TimeVal startup_query_interval = query_interval().get() / 4;
    _query_timer = mld6igmp_node().eventloop().new_oneoff_after(
	startup_query_interval,
	callback(this, &Mld6igmpVif::query_timer_timeout));

    XLOG_INFO("Interface started: %s%s",
	      this->str().c_str(), flags_string().c_str());
    
    return (XORP_OK);
}

/**
 * Mld6igmpVif::stop:
 * @error_msg: The error message (if error).
 * 
 * Stop MLD or IGMP on a single virtual interface.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::stop(string& error_msg)
{
    int ret_value = XORP_OK;

    if (is_down())
	return (XORP_OK);

    if (! (is_up() || is_pending_up() || is_pending_down())) {
	error_msg = "the vif state is not UP or PENDING_UP or PENDING_DOWN";
	return (XORP_ERROR);
    }

    if (ProtoUnit::pending_stop() < 0) {
	error_msg = "internal error";
	ret_value = XORP_ERROR;
    }
    
    //
    // XXX: we don't have to explicitly leave the multicast groups
    // we have joined on that interface, because this will happen
    // automatically when we stop the vif through the MFEA.
    //

    if (ProtoUnit::stop() < 0) {
	error_msg = "internal error";
	ret_value = XORP_ERROR;
    }
    
    set_i_am_querier(false);
    set_querier_addr(IPvX::ZERO(family()));		// XXX: ANY
    _other_querier_timer.unschedule();
    _query_timer.unschedule();
    _igmpv1_router_present_timer.unschedule();
    _startup_query_count = 0;
    
    // Remove all members entries
    map<IPvX, Mld6igmpGroupRecord *>::iterator iter;
    for (iter = _members.begin(); iter != _members.end(); ++iter) {
	Mld6igmpGroupRecord *group_record = iter->second;
	join_prune_notify_routing(IPvX::ZERO(family()),
				  group_record->group(), ACTION_PRUNE);
	delete group_record;
    }
    _members.clear();
    
    //
    // Stop the vif with the kernel
    //
    if (mld6igmp_node().stop_protocol_kernel_vif(vif_index()) != XORP_OK) {
	XLOG_ERROR("Cannot stop protocol vif %s with the kernel",
		   name().c_str());
	ret_value = XORP_ERROR;
    }
    
    XLOG_INFO("Interface stopped: %s%s",
	      this->str().c_str(), flags_string().c_str());

    //
    // Inform the node that the vif has completed the shutdown
    //
    mld6igmp_node().vif_shutdown_completed(name());

    return (ret_value);
}

/**
 * Enable MLD/IGMP on a single virtual interface.
 * 
 * If an unit is not enabled, it cannot be start, or pending-start.
 */
void
Mld6igmpVif::enable()
{
    ProtoUnit::enable();

    XLOG_INFO("Interface enabled: %s%s",
	      this->str().c_str(), flags_string().c_str());
}

/**
 * Disable MLD/IGMP on a single virtual interface.
 * 
 * If an unit is disabled, it cannot be start or pending-start.
 * If the unit was runnning, it will be stop first.
 */
void
Mld6igmpVif::disable()
{
    string error_msg;

    stop(error_msg);
    ProtoUnit::disable();

    XLOG_INFO("Interface disabled: %s%s",
	      this->str().c_str(), flags_string().c_str());
}

/**
 * Mld6igmpVif::mld6igmp_send:
 * @src: The message source address.
 * @dst: The message destination address.
 * @message_type: The MLD or IGMP type of the message.
 * @max_resp_code: The "Maximum Response Code" or "Max Resp Code"
 * field in the MLD or IGMP headers respectively (in the particular
 * protocol resolution).
 * @group_address: The "Multicast Address" or "Group Address" field
 * in the MLD or IGMP headers respectively.
 * @error_msg: The error message (if error).
 * 
 * Send MLD or IGMP message.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::mld6igmp_send(const IPvX& src,
			   const IPvX& dst,
			   uint8_t message_type,
			   uint16_t max_resp_code,
			   const IPvX& group_address,
			   string& error_msg)
{
    uint16_t cksum;
    buffer_t *buffer;
    int ret_value;
    
    if (! (is_up() || is_pending_down())) {
	error_msg = c_format("vif %s is not UP", name().c_str());
	return (XORP_ERROR);
    }
    
    XLOG_ASSERT(src != IPvX::ZERO(family()));
    
    //
    // Prepare the MLD or IGMP header.
    //
    buffer = buffer_send_prepare();
    if (proto_is_igmp()) {
	BUFFER_PUT_OCTET(message_type, buffer);	// The message type
	BUFFER_PUT_OCTET(max_resp_code, buffer);
	BUFFER_PUT_HOST_16(0, buffer);		// Zero the checksum field
	BUFFER_PUT_IPVX(group_address, buffer);
    }
    if (proto_is_mld6()) {
	BUFFER_PUT_OCTET(message_type, buffer);	// The message type
	BUFFER_PUT_OCTET(0, buffer);		// XXX: Always 0 for MLD
	BUFFER_PUT_HOST_16(0, buffer);		// Zero the checksum field
	BUFFER_PUT_HOST_16(max_resp_code, buffer);
	BUFFER_PUT_HOST_16(0, buffer);		// Reserved
	BUFFER_PUT_IPVX(group_address, buffer);
    }

    //
    // Compute the checksum
    //
    cksum = INET_CKSUM(BUFFER_DATA_HEAD(buffer), BUFFER_DATA_SIZE(buffer));
#ifdef HAVE_IPV6_MULTICAST_ROUTING
    // Add the checksum for the IPv6 pseudo-header
    if (proto_is_mld6()) {
	struct pseudo_header {
	    struct in6_addr in6_src;
	    struct in6_addr in6_dst;
	    uint32_t pkt_len;
	    uint32_t next_header;
	} pseudo_header;
	
	src.copy_out(pseudo_header.in6_src);
	dst.copy_out(pseudo_header.in6_dst);
	pseudo_header.pkt_len = ntohl(BUFFER_DATA_SIZE(buffer));
	pseudo_header.next_header = htonl(IPPROTO_ICMPV6);
	
	uint16_t cksum2 = INET_CKSUM(&pseudo_header, sizeof(pseudo_header));
	cksum = INET_CKSUM_ADD(cksum, cksum2);
    }
#endif // HAVE_IPV6_MULTICAST_ROUTING
    BUFFER_COPYPUT_INET_CKSUM(cksum, buffer, 2);	// XXX: the ckecksum
    
    XLOG_TRACE(mld6igmp_node().is_log_trace(), "TX %s from %s to %s",
	       proto_message_type2ascii(message_type),
	       cstring(src),
	       cstring(dst));
    
    //
    // Send the message
    //
    ret_value = mld6igmp_node().mld6igmp_send(vif_index(), src, dst,
					      MINTTL, -1, true, buffer,
					      error_msg);
    
    return (ret_value);
    
 buflen_error:
    XLOG_UNREACHABLE();
    error_msg = c_format("TX %s from %s to %s: "
			 "packet cannot fit into sending buffer",
			 proto_message_type2ascii(message_type),
			 cstring(src),
			 cstring(dst));
    XLOG_ERROR("%s", error_msg.c_str());
    return (XORP_ERROR);
}

/**
 * Mld6igmpVif::mld6igmp_recv:
 * @src: The message source address.
 * @dst: The message destination address.
 * @ip_ttl: The IP TTL of the message. If it has a negative value,
 * it should be ignored.
 * @ip_tos: The IP TOS of the message. If it has a negative value,
 * it should be ignored.
 * @is_router_alert: True if the received IP packet had the Router Alert
 * IP option set.
 * @buffer: The buffer with the received message.
 * @error_msg: The error message (if error).
 * 
 * Receive MLD or IGMP message and pass it for processing.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::mld6igmp_recv(const IPvX& src,
			   const IPvX& dst,
			   int ip_ttl,
			   int ip_tos,
			   bool is_router_alert,
			   buffer_t *buffer,
			   string& error_msg)
{
    int ret_value = XORP_ERROR;
    
    if (! is_up()) {
	error_msg = c_format("vif %s is not UP", name().c_str());
	return (XORP_ERROR);
    }
    
    ret_value = mld6igmp_process(src, dst, ip_ttl, ip_tos, is_router_alert,
				 buffer, error_msg);
    
    return (ret_value);
}

/**
 * Mld6igmpVif::mld6igmp_process:
 * @src: The message source address.
 * @dst: The message destination address.
 * @ip_ttl: The IP TTL of the message. If it has a negative value,
 * it should be ignored.
 * @ip_tos: The IP TOS of the message. If it has a negative value,
 * it should be ignored.
 * @is_router_alert: True if the received IP packet had the Router Alert
 * IP option set.
 * @buffer: The buffer with the message.
 * @error_msg: The error message (if error).
 * 
 * Process MLD or IGMP message and pass the control to the type-specific
 * functions.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::mld6igmp_process(const IPvX& src,
			      const IPvX& dst,
			      int ip_ttl,
			      int ip_tos,
			      bool is_router_alert,
			      buffer_t *buffer,
			      string& error_msg)
{
#if defined(HAVE_IPV4_MULTICAST_ROUTING) || defined(HAVE_IPV6_MULTICAST_ROUTING)
    uint8_t message_type = 0;
    uint16_t max_resp_code = 0;
    IPvX group_address(family());
    uint16_t cksum;
    bool check_router_alert_option = false;
    bool check_src_linklocal_unicast = false;
    bool check_dst_multicast = false;
    bool check_group_nodelocal_multicast = false;
    bool decode_extra_fields = false;
    
    //
    // Message length check.
    //
    if (BUFFER_DATA_SIZE(buffer) < mld6igmp_constant_minlen()) {
	error_msg = c_format("RX packet from %s to %s on vif %s: "
			     "too short data field (%u octets)",
			     cstring(src), cstring(dst),
			     name().c_str(),
			     XORP_UINT_CAST(BUFFER_DATA_SIZE(buffer)));
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }
    
    //
    // Checksum verification.
    //
    cksum = INET_CKSUM(BUFFER_DATA_HEAD(buffer), BUFFER_DATA_SIZE(buffer));
#ifdef HAVE_IPV6_MULTICAST_ROUTING
    // Add the checksum for the IPv6 pseudo-header
    if (proto_is_mld6()) {
	struct pseudo_header {
	    struct in6_addr in6_src;
	    struct in6_addr in6_dst;
	    uint32_t pkt_len;
	    uint32_t next_header;
	} pseudo_header;
	
	src.copy_out(pseudo_header.in6_src);
	dst.copy_out(pseudo_header.in6_dst);
	pseudo_header.pkt_len = ntohl(BUFFER_DATA_SIZE(buffer));
	pseudo_header.next_header = htonl(IPPROTO_ICMPV6);
	
	uint16_t cksum2 = INET_CKSUM(&pseudo_header, sizeof(pseudo_header));
	cksum = INET_CKSUM_ADD(cksum, cksum2);
    }
#endif // HAVE_IPV6_MULTICAST_ROUTING
    if (cksum) {
	error_msg = c_format("RX packet from %s to %s on vif %s: "
			     "checksum error",
			     cstring(src), cstring(dst),
			     name().c_str());
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }
    
    //
    // Protocol version check.
    //
    // XXX: MLD and IGMP messages do not have an explicit field for protocol
    // version. Protocol version check is performed later, per (some) message
    // type.
    //
    
    //
    // Get the message type and the max. resp. time (in case of IGMP).
    //
    // Note that in case of IGMP the max. resp. time is the `igmp_code' field
    // in `struct igmp'.
    //
    if (proto_is_igmp()) {
	BUFFER_GET_OCTET(message_type, buffer);
	BUFFER_GET_OCTET(max_resp_code, buffer);
	BUFFER_GET_SKIP(2, buffer);		// The checksum
    }
    if (proto_is_mld6()) {
	BUFFER_GET_OCTET(message_type, buffer);
	BUFFER_GET_SKIP(1, buffer);		// The `Code' field: unused
	BUFFER_GET_SKIP(2, buffer);		// The `Checksum' field
    }

    XLOG_TRACE(mld6igmp_node().is_log_trace(),
	       "RX %s from %s to %s on vif %s",
	       proto_message_type2ascii(message_type),
	       cstring(src), cstring(dst),
	       name().c_str());

    //
    // Assign various flags what needs to be checked, based on the
    // message type:
    //  - check_router_alert_option
    //  - check_src_linklocal_unicast
    //  - check_dst_multicast
    //  - check_group_nodelocal_multicast
    //  - decode_extra_fields
    //
#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp()) {
	switch (message_type) {
	case IGMP_MEMBERSHIP_QUERY:
	case IGMP_V1_MEMBERSHIP_REPORT:
	case IGMP_V2_MEMBERSHIP_REPORT:
	case IGMP_V2_LEAVE_GROUP:
	case IGMP_V3_MEMBERSHIP_REPORT:
	    if (_ip_router_alert_option_check.get())
		check_router_alert_option = true;
	    check_src_linklocal_unicast = false;	// Not needed for IPv4
	    check_dst_multicast = true;
	    check_group_nodelocal_multicast = false;	// Not needed for IPv4
	    decode_extra_fields = true;
	    if (message_type == IGMP_V3_MEMBERSHIP_REPORT)
		decode_extra_fields = false;
	    break;
	case IGMP_DVMRP:
	case IGMP_MTRACE:
	    // TODO: Assign the flags as appropriate
	    break;
	default:
	    break;
	}
    }
#endif // HAVE_IPV4_MULTICAST_ROUTING

#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6()) {
	switch (message_type) {
	case MLD_LISTENER_QUERY:
	case MLD_LISTENER_REPORT:
	case MLD_LISTENER_DONE:
	case MLDV2_LISTENER_REPORT:
	    check_router_alert_option = true;
	    check_src_linklocal_unicast = true;
	    check_dst_multicast = true;
	    check_group_nodelocal_multicast = true;
	    decode_extra_fields = true;
	    if (message_type == MLDV2_LISTENER_REPORT)
		decode_extra_fields = false;
	    break;
	case MLD_MTRACE:
	    // TODO: Assign the flags as appropriate
	    break;
	default:
	    break;
	}
    }
#endif // HAVE_IPV6_MULTICAST_ROUTING

    //
    // Decode the extra fields: the max. resp. time (in case of MLD),
    // and the group address.
    //
    if (decode_extra_fields) {
	if (proto_is_igmp()) {
	    BUFFER_GET_IPVX(family(), group_address, buffer);
	}
	if (proto_is_mld6()) {
	    BUFFER_GET_HOST_16(max_resp_code, buffer);
	    BUFFER_GET_SKIP(2, buffer);		// The `Reserved' field
	    BUFFER_GET_IPVX(family(), group_address, buffer);
	}
    }

    //
    // IP Router Alert option check.
    //
    if (check_router_alert_option && (! is_router_alert)) {
	error_msg = c_format("RX %s from %s to %s on vif %s: "
			     "missing IP Router Alert option",
			     proto_message_type2ascii(message_type),
			     cstring(src), cstring(dst),
			     name().c_str());
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }
    //
    // TODO: check the TTL and TOS if we are running in secure mode
    //
    UNUSED(ip_ttl);
    UNUSED(ip_tos);
#if 0
    if (ip_ttl != MINTTL) {
	error_msg = c_format("RX %s from %s to %s on vif %s: "
			     "ip_ttl = %d instead of %d",
			     proto_message_type2ascii(message_type),
			     cstring(src), cstring(dst),
			     name().c_str(),
			     ip_ttl, MINTTL);
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }
#endif // 0
    
    //
    // Source address check.
    //
    if (! src.is_unicast()) {
	//
	// Source address must always be unicast.
	// The kernel should have checked that, but just in case...
	//
	error_msg = c_format("RX %s from %s to %s on vif %s: "
			     "source must be unicast",
			     proto_message_type2ascii(message_type),
			     cstring(src), cstring(dst),
			     name().c_str());
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }
    if (src.af() != family()) {
	// Invalid source address family
	XLOG_WARNING("RX %s from %s to %s on vif %s: "
		     "invalid source address family "
		     "(received %d expected %d)",
		     proto_message_type2ascii(message_type),
		     cstring(src), cstring(dst),
		     name().c_str(),
		     src.af(), family());
    }
    if (check_src_linklocal_unicast && (! src.is_linklocal_unicast())) {
	// The source address is not link-local
	error_msg = c_format("RX %s from %s to %s on vif %s: "
			     "source is not a link-local address",
			     proto_message_type2ascii(message_type),
			     cstring(src), cstring(dst),
			     name().c_str());
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }

    //
    // Destination address check.
    //
    if (dst.af() != family()) {
	// Invalid destination address family
	XLOG_WARNING("RX %s from %s to %s on vif %s: "
		     "invalid destination address family "
		     "(received %d expected %d)",
		     proto_message_type2ascii(message_type),
		     cstring(src), cstring(dst),
		     name().c_str(),
		     dst.af(), family());
    }
    if (check_dst_multicast && (! dst.is_multicast())) {
	// The destination address is not multicast
	error_msg = c_format("RX %s from %s to %s on vif %s: "
			     "destination must be multicast. "
			     "Packet ignored.",
			     proto_message_type2ascii(message_type),
			     cstring(src), cstring(dst),
			     name().c_str());
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }

    //
    // Inner multicast address scope check.
    //
    if (check_group_nodelocal_multicast
	&& group_address.is_nodelocal_multicast()) {
	error_msg = c_format("RX %s from %s to %s on vif %s: "
			     "invalid node-local scope of inner "
			     "multicast address: %s",
			     proto_message_type2ascii(message_type),
			     cstring(src), cstring(dst),
			     name().c_str(),
			     cstring(group_address));
	XLOG_WARNING("%s", error_msg.c_str());
	return (XORP_ERROR);
    }

    //
    // Origin router neighbor check.
    //
    // XXX: in IGMP and MLD we don't need such check
    
    //
    // Process each message, based on its type.
    //
#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp()) {
	switch (message_type) {
	case IGMP_MEMBERSHIP_QUERY:
	    mld6igmp_membership_query_recv(src, dst,
					   message_type, max_resp_code,
					   group_address, buffer);
	    break;
	case IGMP_V1_MEMBERSHIP_REPORT:
	case IGMP_V2_MEMBERSHIP_REPORT:
	    mld6igmp_membership_report_recv(src, dst,
					    message_type, max_resp_code,
					    group_address, buffer);
	    break;
	case IGMP_V2_LEAVE_GROUP:
	    mld6igmp_leave_group_recv(src, dst,
				      message_type, max_resp_code,
				      group_address, buffer);
	    break;
	case IGMP_V3_MEMBERSHIP_REPORT:
	    mld6igmp_ssm_membership_report_recv(src, dst, message_type,
						buffer);
	    break;
	case IGMP_DVMRP:
	{
	    //
	    // XXX: We care only about the DVMRP messages that are used
	    // by mrinfo.
	    //
	    // XXX: the older purpose of the 'igmp_code' field
	    uint16_t igmp_code = max_resp_code;
	    switch (igmp_code) {
	    case DVMRP_ASK_NEIGHBORS:
		// Some old DVMRP messages from mrinfo(?).
		// TODO: not implemented yet.
		// TODO: do we really need this message implemented?
		break;
	    case DVMRP_ASK_NEIGHBORS2:
		// Used for mrinfo support.
		// XXX: not implemented yet.
		break;
	    case DVMRP_INFO_REQUEST:
		// Information request (TODO: used by mrinfo?)
		// TODO: not implemented yet.
		break;
	    default:
		// XXX: We don't care about the rest of the DVMRP_* messages
		break;
	    }
	}
	case IGMP_MTRACE:
	    // TODO: is this the new message sent by 'mtrace'?
	    // TODO: not implemented yet.
	    break;
	default:
	    // XXX: Unrecognized message types MUST be silently ignored.
	    break;
	}
    }
#endif // HAVE_IPV4_MULTICAST_ROUTING

#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6()) {
	switch (message_type) {
	case MLD_LISTENER_QUERY:
	    mld6igmp_membership_query_recv(src, dst,
					   message_type, max_resp_code,
					   group_address, buffer);
	    break;
	case MLD_LISTENER_REPORT:
	    mld6igmp_membership_report_recv(src, dst,
					    message_type, max_resp_code,
					    group_address, buffer);
	    break;
	case MLD_LISTENER_DONE:
	    mld6igmp_leave_group_recv(src, dst,
				      message_type, max_resp_code,
				      group_address, buffer);
	    break;
	case MLDV2_LISTENER_REPORT:
	    mld6igmp_ssm_membership_report_recv(src, dst, message_type,
						buffer);
	    break;
	case MLD_MTRACE:
	    // TODO: is this the new message sent by 'mtrace'?
	    // TODO: not implemented yet.
	    break;
	default:
	    // XXX: Unrecognized message types MUST be silently ignored.
	    break;
	}
    }
#endif // HAVE_IPV6_MULTICAST_ROUTING

    return (XORP_OK);

 rcvlen_error:
    XLOG_UNREACHABLE();
    error_msg = c_format("RX packet from %s to %s on vif %s: "
			 "some fields are too short",
			 cstring(src), cstring(dst),
			 name().c_str());
    XLOG_WARNING("%s", error_msg.c_str());
    return (XORP_ERROR);

#else // ! (HAVE_IPV4_MULTICAST_ROUTING || HAVE_IPV6_MULTICAST_ROUTING)

    XLOG_WARNING("The system does not support multicast routing");

    UNUSED(src);
    UNUSED(dst);
    UNUSED(ip_ttl);
    UNUSED(ip_tos);
    UNUSED(is_router_alert);
    UNUSED(buffer);
    UNUSED(error_msg);

    return (XORP_ERROR);
#endif // ! (HAVE_IPV4_MULTICAST_ROUTING || HAVE_IPV6_MULTICAST_ROUTING)
}

/**
 * Mld6igmpVif::update_primary_address:
 * @error_msg: The error message (if error).
 * 
 * Update the primary address.
 * 
 * The primary address should be a link-local unicast address, and
 * is used for transmitting the multicast control packets on the LAN.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::update_primary_address(string& error_msg)
{
    bool i_was_querier = false;
    IPvX primary_a(IPvX::ZERO(family()));
    IPvX domain_wide_a(IPvX::ZERO(family()));

    //
    // Reset the primary address if it is not valid anymore.
    //
    if (Vif::find_address(primary_addr()) == NULL) {
	if (primary_addr() == querier_addr()) {
	    // Reset the querier address
	    set_querier_addr(IPvX::ZERO(family()));
	    set_i_am_querier(false);
	    i_was_querier = true;
	}
	set_primary_addr(IPvX::ZERO(family()));
    }

    list<VifAddr>::const_iterator iter;
    for (iter = addr_list().begin(); iter != addr_list().end(); ++iter) {
	const VifAddr& vif_addr = *iter;
	const IPvX& addr = vif_addr.addr();
	if (! addr.is_unicast())
	    continue;
	if (addr.is_linklocal_unicast()) {
	    if (primary_a.is_zero())
		primary_a = addr;
	    continue;
	}
	//
	// XXX: assume that everything else can be a domain-wide reachable
	// address.
	if (domain_wide_a.is_zero())
	    domain_wide_a = addr;
    }

    //
    // XXX: In case of IPv6 if there is no link-local address we may try
    // to use the the domain-wide address as a primary address,
    // but the MLD spec is clear that the MLD messages are to be originated
    // from a link-local address.
    // Hence, only in case of IPv4 we assign the domain-wide address
    // to the primary address.
    //
    if (is_ipv4()) {
	if (primary_a.is_zero())
	    primary_a = domain_wide_a;
    }

    //
    // Check that the interface has a primary address.
    //
    if (primary_addr().is_zero() && primary_a.is_zero()) {
	error_msg = "invalid primary address";
	return (XORP_ERROR);
    }
    
    if (primary_addr().is_zero())
	set_primary_addr(primary_a);

    if (i_was_querier) {
	// Assume again that I am the MLD6IGMP Querier
	set_querier_addr(primary_addr());
	set_i_am_querier(true);
    }

    return (XORP_OK);
}

/**
 * Mld6igmpVif::add_protocol:
 * @module_id: The #xorp_module_id of the protocol to add.
 * @module_instance_name: The module instance name of the protocol to add.
 * 
 * Add a protocol to the list of entries that would be notified if there
 * is membership change on this interface.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::add_protocol(xorp_module_id module_id,
			  const string& module_instance_name)
{
    if (find(_notify_routing_protocols.begin(),
	     _notify_routing_protocols.end(),
	     pair<xorp_module_id, string>(module_id, module_instance_name))
	!= _notify_routing_protocols.end()) {
	return (XORP_ERROR);		// Already added
    }
    
    _notify_routing_protocols.push_back(
	pair<xorp_module_id, string>(module_id, module_instance_name));
    
    return (XORP_OK);
}

/**
 * Mld6igmpVif::delete_protocol:
 * @module_id: The #xorp_module_id of the protocol to delete.
 * @module_instance_name: The module instance name of the protocol to delete.
 * 
 * Delete a protocol from the list of entries that would be notified if there
 * is membership change on this interface.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::delete_protocol(xorp_module_id module_id,
			     const string& module_instance_name)
{
    vector<pair<xorp_module_id, string> >::iterator iter;
    
    iter = find(_notify_routing_protocols.begin(),
		_notify_routing_protocols.end(),
		pair<xorp_module_id, string>(module_id, module_instance_name));
    
    if (iter == _notify_routing_protocols.end())
	return (XORP_ERROR);		// Not on the list
    
    _notify_routing_protocols.erase(iter);
    
    return (XORP_OK);
}

/**
 * Mld6igmpVif::is_igmpv1_mode:
 * @: 
 * 
 * Tests if the interface is running in IGMPv1 mode.
 * XXX: applies only to IGMP, and not to MLD.
 * 
 * Return value: true if the interface is running in IGMPv1 mode,
 * otherwise false.
 **/
bool
Mld6igmpVif::is_igmpv1_mode() const
{
    return (proto_is_igmp()
	    && ((proto_version() == IGMP_V1)
		|| _igmpv1_router_present_timer.scheduled()));
}

/**
 * Mld6igmpVif::proto_message_type2ascii:
 * @message_type: The protocol message type.
 * 
 * Return the ASCII text description of the protocol message.
 * 
 * Return value: The ASCII text descrpition of the protocol message.
 **/
const char *
Mld6igmpVif::proto_message_type2ascii(uint8_t message_type) const
{

    UNUSED(message_type);

#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp())
	return (IGMPTYPE2ASCII(message_type));
#endif

#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6())
	return (MLDTYPE2ASCII(message_type));
#endif
    
    return ("Unknown protocol message");
}

/**
 * Mld6igmpVif::buffer_send_prepare:
 * @: 
 * 
 * Reset and prepare the buffer for sending data.
 * 
 * Return value: The prepared buffer.
 **/
buffer_t *
Mld6igmpVif::buffer_send_prepare()
{
    BUFFER_RESET(_buffer_send);
    
    return (_buffer_send);
}

/**
 * Mld6igmpVif::join_prune_notify_routing:
 * @source: The source address of the (S,G) entry that has changed.
 * In case of group-specific membership, it could be NULL.
 * @group: The group address of the (S,G) entry that has changed.
 * @action_jp: The membership change: %ACTION_JOIN or %ACTION_PRUNE.
 * 
 * Notify the interested parties that there is membership change among
 * the local members.
 * 
 * Return value: %XORP_OK on success, otherwise %XORP_ERROR.
 **/
int
Mld6igmpVif::join_prune_notify_routing(const IPvX& source,
				       const IPvX& group,
				       action_jp_t action_jp) const
{
    vector<pair<xorp_module_id, string> >::const_iterator iter;
    for (iter = _notify_routing_protocols.begin();
	 iter != _notify_routing_protocols.end();
	 ++iter) {
	pair<xorp_module_id, string> my_pair = *iter;
	xorp_module_id module_id = my_pair.first;
	string module_instance_name = my_pair.second;

	if (mld6igmp_node().join_prune_notify_routing(module_instance_name,
						      module_id,
						      vif_index(),
						      source,
						      group,
						      action_jp) < 0) {
	    //
	    // TODO: remove <module_id, module_instance_name> ??
	    //
	}
    }
    
    return (XORP_OK);
}

bool
Mld6igmpVif::i_am_querier() const
{
    if (_proto_flags & MLD6IGMP_VIF_QUERIER)
	return (true);
    else
	return (false);
}

void
Mld6igmpVif::set_i_am_querier(bool v)
{
    if (v)
	_proto_flags |= MLD6IGMP_VIF_QUERIER;
    else
	_proto_flags &= ~MLD6IGMP_VIF_QUERIER;
}

size_t
Mld6igmpVif::mld6igmp_constant_minlen() const
{
#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp())
	return (IGMP_MINLEN);
#endif

#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6())
	return (MLD_MINLEN);
#endif

    XLOG_UNREACHABLE();
    return (0);
}

uint32_t
Mld6igmpVif::mld6igmp_constant_timer_scale() const
{
#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp())
	return (IGMP_TIMER_SCALE);
#endif

#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6())
	return (MLD_TIMER_SCALE);
#endif

    XLOG_UNREACHABLE();
    return (0);
}

uint8_t
Mld6igmpVif::mld6igmp_constant_membership_query() const
{
#ifdef HAVE_IPV4_MULTICAST_ROUTING
    if (proto_is_igmp())
	return (IGMP_MEMBERSHIP_QUERY);
#endif

#ifdef HAVE_IPV6_MULTICAST_ROUTING
    if (proto_is_mld6())
	return (MLD_LISTENER_QUERY);
#endif

    XLOG_UNREACHABLE();
    return (0);
}

// TODO: temporary here. Should go to the Vif class after the Vif
// class starts using the Proto class
string
Mld6igmpVif::flags_string() const
{
    string flags;
    
    if (is_up())
	flags += " UP";
    if (is_down())
	flags += " DOWN";
    if (is_pending_up())
	flags += " PENDING_UP";
    if (is_pending_down())
	flags += " PENDING_DOWN";
    if (is_ipv4())
	flags += " IPv4";
    if (is_ipv6())
	flags += " IPv6";
    if (is_enabled())
	flags += " ENABLED";
    if (is_disabled())
	flags += " DISABLED";
    
    return (flags);
}
