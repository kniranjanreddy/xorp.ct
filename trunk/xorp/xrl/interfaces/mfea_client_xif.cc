/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/mfea_client_xif.cc,v 1.11 2003/08/07 04:52:26 hodson Exp $"

#include "mfea_client_xif.hh"

bool
XrlMfeaClientV0p1Client::send_new_vif(
	const char*	the_tgt,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const NewVifCB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/new_vif");
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_new_vif, cb));
}


/* Unmarshall new_vif */
void
XrlMfeaClientV0p1Client::unmarshall_new_vif(
	const XrlError&	e,
	XrlArgs*	a,
	NewVifCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_delete_vif(
	const char*	the_tgt,
	const string&	vif_name,
	const DeleteVifCB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/delete_vif");
    x.args().add("vif_name", vif_name);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_delete_vif, cb));
}


/* Unmarshall delete_vif */
void
XrlMfeaClientV0p1Client::unmarshall_delete_vif(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteVifCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_add_vif_addr4(
	const char*	the_tgt,
	const string&	vif_name,
	const IPv4&	addr,
	const IPv4Net&	subnet,
	const IPv4&	broadcast,
	const IPv4&	peer,
	const AddVifAddr4CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/add_vif_addr4");
    x.args().add("vif_name", vif_name);
    x.args().add("addr", addr);
    x.args().add("subnet", subnet);
    x.args().add("broadcast", broadcast);
    x.args().add("peer", peer);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_add_vif_addr4, cb));
}


/* Unmarshall add_vif_addr4 */
void
XrlMfeaClientV0p1Client::unmarshall_add_vif_addr4(
	const XrlError&	e,
	XrlArgs*	a,
	AddVifAddr4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_add_vif_addr6(
	const char*	the_tgt,
	const string&	vif_name,
	const IPv6&	addr,
	const IPv6Net&	subnet,
	const IPv6&	broadcast,
	const IPv6&	peer,
	const AddVifAddr6CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/add_vif_addr6");
    x.args().add("vif_name", vif_name);
    x.args().add("addr", addr);
    x.args().add("subnet", subnet);
    x.args().add("broadcast", broadcast);
    x.args().add("peer", peer);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_add_vif_addr6, cb));
}


/* Unmarshall add_vif_addr6 */
void
XrlMfeaClientV0p1Client::unmarshall_add_vif_addr6(
	const XrlError&	e,
	XrlArgs*	a,
	AddVifAddr6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_delete_vif_addr4(
	const char*	the_tgt,
	const string&	vif_name,
	const IPv4&	addr,
	const DeleteVifAddr4CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/delete_vif_addr4");
    x.args().add("vif_name", vif_name);
    x.args().add("addr", addr);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_delete_vif_addr4, cb));
}


/* Unmarshall delete_vif_addr4 */
void
XrlMfeaClientV0p1Client::unmarshall_delete_vif_addr4(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteVifAddr4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_delete_vif_addr6(
	const char*	the_tgt,
	const string&	vif_name,
	const IPv6&	addr,
	const DeleteVifAddr6CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/delete_vif_addr6");
    x.args().add("vif_name", vif_name);
    x.args().add("addr", addr);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_delete_vif_addr6, cb));
}


/* Unmarshall delete_vif_addr6 */
void
XrlMfeaClientV0p1Client::unmarshall_delete_vif_addr6(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteVifAddr6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_set_vif_flags(
	const char*	the_tgt,
	const string&	vif_name,
	const bool&	is_pim_register,
	const bool&	is_p2p,
	const bool&	is_loopback,
	const bool&	is_multicast,
	const bool&	is_broadcast,
	const bool&	is_up,
	const SetVifFlagsCB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/set_vif_flags");
    x.args().add("vif_name", vif_name);
    x.args().add("is_pim_register", is_pim_register);
    x.args().add("is_p2p", is_p2p);
    x.args().add("is_loopback", is_loopback);
    x.args().add("is_multicast", is_multicast);
    x.args().add("is_broadcast", is_broadcast);
    x.args().add("is_up", is_up);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_set_vif_flags, cb));
}


/* Unmarshall set_vif_flags */
void
XrlMfeaClientV0p1Client::unmarshall_set_vif_flags(
	const XrlError&	e,
	XrlArgs*	a,
	SetVifFlagsCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_set_all_vifs_done(
	const char*	the_tgt,
	const SetAllVifsDoneCB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/set_all_vifs_done");
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_set_all_vifs_done, cb));
}


/* Unmarshall set_all_vifs_done */
void
XrlMfeaClientV0p1Client::unmarshall_set_all_vifs_done(
	const XrlError&	e,
	XrlArgs*	a,
	SetAllVifsDoneCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_is_vif_setup_completed(
	const char*	the_tgt,
	const IsVifSetupCompletedCB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/is_vif_setup_completed");
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_is_vif_setup_completed, cb));
}


/* Unmarshall is_vif_setup_completed */
void
XrlMfeaClientV0p1Client::unmarshall_is_vif_setup_completed(
	const XrlError&	e,
	XrlArgs*	a,
	IsVifSetupCompletedCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e, 0);
	return;
    } else if (a && a->size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 1);
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    bool is_completed;
    try {
	a->get("is_completed", is_completed);
    } catch (const XrlArgs::XrlAtomNotFound&) {
	XLOG_ERROR("Atom not found");
	cb->dispatch(XrlError::BAD_ARGS(), 0);
	return;
    }
    cb->dispatch(e, &is_completed);
}

bool
XrlMfeaClientV0p1Client::send_recv_protocol_message4(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv4&	source_address,
	const IPv4&	dest_address,
	const int32_t&	ip_ttl,
	const int32_t&	ip_tos,
	const bool&	is_router_alert,
	const vector<uint8_t>&	protocol_message,
	const RecvProtocolMessage4CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/recv_protocol_message4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source_address", source_address);
    x.args().add("dest_address", dest_address);
    x.args().add("ip_ttl", ip_ttl);
    x.args().add("ip_tos", ip_tos);
    x.args().add("is_router_alert", is_router_alert);
    x.args().add("protocol_message", protocol_message);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_protocol_message4, cb));
}


/* Unmarshall recv_protocol_message4 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_protocol_message4(
	const XrlError&	e,
	XrlArgs*	a,
	RecvProtocolMessage4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_recv_protocol_message6(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv6&	source_address,
	const IPv6&	dest_address,
	const int32_t&	ip_ttl,
	const int32_t&	ip_tos,
	const bool&	is_router_alert,
	const vector<uint8_t>&	protocol_message,
	const RecvProtocolMessage6CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/recv_protocol_message6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source_address", source_address);
    x.args().add("dest_address", dest_address);
    x.args().add("ip_ttl", ip_ttl);
    x.args().add("ip_tos", ip_tos);
    x.args().add("is_router_alert", is_router_alert);
    x.args().add("protocol_message", protocol_message);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_protocol_message6, cb));
}


/* Unmarshall recv_protocol_message6 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_protocol_message6(
	const XrlError&	e,
	XrlArgs*	a,
	RecvProtocolMessage6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_recv_kernel_signal_message4(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const uint32_t&	message_type,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv4&	source_address,
	const IPv4&	dest_address,
	const vector<uint8_t>&	protocol_message,
	const RecvKernelSignalMessage4CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/recv_kernel_signal_message4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("message_type", message_type);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source_address", source_address);
    x.args().add("dest_address", dest_address);
    x.args().add("protocol_message", protocol_message);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message4, cb));
}


/* Unmarshall recv_kernel_signal_message4 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message4(
	const XrlError&	e,
	XrlArgs*	a,
	RecvKernelSignalMessage4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_recv_kernel_signal_message6(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const string&	protocol_name,
	const uint32_t&	protocol_id,
	const uint32_t&	message_type,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv6&	source_address,
	const IPv6&	dest_address,
	const vector<uint8_t>&	protocol_message,
	const RecvKernelSignalMessage6CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/recv_kernel_signal_message6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("protocol_name", protocol_name);
    x.args().add("protocol_id", protocol_id);
    x.args().add("message_type", message_type);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source_address", source_address);
    x.args().add("dest_address", dest_address);
    x.args().add("protocol_message", protocol_message);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message6, cb));
}


/* Unmarshall recv_kernel_signal_message6 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message6(
	const XrlError&	e,
	XrlArgs*	a,
	RecvKernelSignalMessage6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_add_mrib4(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const IPv4Net&	dest_prefix,
	const IPv4&	next_hop_router_addr,
	const string&	next_hop_vif_name,
	const uint32_t&	next_hop_vif_index,
	const uint32_t&	metric_preference,
	const uint32_t&	metric,
	const AddMrib4CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/add_mrib4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("dest_prefix", dest_prefix);
    x.args().add("next_hop_router_addr", next_hop_router_addr);
    x.args().add("next_hop_vif_name", next_hop_vif_name);
    x.args().add("next_hop_vif_index", next_hop_vif_index);
    x.args().add("metric_preference", metric_preference);
    x.args().add("metric", metric);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_add_mrib4, cb));
}


/* Unmarshall add_mrib4 */
void
XrlMfeaClientV0p1Client::unmarshall_add_mrib4(
	const XrlError&	e,
	XrlArgs*	a,
	AddMrib4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_add_mrib6(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const IPv6Net&	dest_prefix,
	const IPv6&	next_hop_router_addr,
	const string&	next_hop_vif_name,
	const uint32_t&	next_hop_vif_index,
	const uint32_t&	metric_preference,
	const uint32_t&	metric,
	const AddMrib6CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/add_mrib6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("dest_prefix", dest_prefix);
    x.args().add("next_hop_router_addr", next_hop_router_addr);
    x.args().add("next_hop_vif_name", next_hop_vif_name);
    x.args().add("next_hop_vif_index", next_hop_vif_index);
    x.args().add("metric_preference", metric_preference);
    x.args().add("metric", metric);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_add_mrib6, cb));
}


/* Unmarshall add_mrib6 */
void
XrlMfeaClientV0p1Client::unmarshall_add_mrib6(
	const XrlError&	e,
	XrlArgs*	a,
	AddMrib6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_delete_mrib4(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const IPv4Net&	dest_prefix,
	const DeleteMrib4CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/delete_mrib4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("dest_prefix", dest_prefix);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_delete_mrib4, cb));
}


/* Unmarshall delete_mrib4 */
void
XrlMfeaClientV0p1Client::unmarshall_delete_mrib4(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteMrib4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_delete_mrib6(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const IPv6Net&	dest_prefix,
	const DeleteMrib6CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/delete_mrib6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("dest_prefix", dest_prefix);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_delete_mrib6, cb));
}


/* Unmarshall delete_mrib6 */
void
XrlMfeaClientV0p1Client::unmarshall_delete_mrib6(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteMrib6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_set_mrib_done(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const SetMribDoneCB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/set_mrib_done");
    x.args().add("xrl_sender_name", xrl_sender_name);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_set_mrib_done, cb));
}


/* Unmarshall set_mrib_done */
void
XrlMfeaClientV0p1Client::unmarshall_set_mrib_done(
	const XrlError&	e,
	XrlArgs*	a,
	SetMribDoneCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_recv_dataflow_signal4(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const IPv4&	source_address,
	const IPv4&	group_address,
	const uint32_t&	threshold_interval_sec,
	const uint32_t&	threshold_interval_usec,
	const uint32_t&	measured_interval_sec,
	const uint32_t&	measured_interval_usec,
	const uint32_t&	threshold_packets,
	const uint32_t&	threshold_bytes,
	const uint32_t&	measured_packets,
	const uint32_t&	measured_bytes,
	const bool&	is_threshold_in_packets,
	const bool&	is_threshold_in_bytes,
	const bool&	is_geq_upcall,
	const bool&	is_leq_upcall,
	const RecvDataflowSignal4CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/recv_dataflow_signal4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("source_address", source_address);
    x.args().add("group_address", group_address);
    x.args().add("threshold_interval_sec", threshold_interval_sec);
    x.args().add("threshold_interval_usec", threshold_interval_usec);
    x.args().add("measured_interval_sec", measured_interval_sec);
    x.args().add("measured_interval_usec", measured_interval_usec);
    x.args().add("threshold_packets", threshold_packets);
    x.args().add("threshold_bytes", threshold_bytes);
    x.args().add("measured_packets", measured_packets);
    x.args().add("measured_bytes", measured_bytes);
    x.args().add("is_threshold_in_packets", is_threshold_in_packets);
    x.args().add("is_threshold_in_bytes", is_threshold_in_bytes);
    x.args().add("is_geq_upcall", is_geq_upcall);
    x.args().add("is_leq_upcall", is_leq_upcall);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal4, cb));
}


/* Unmarshall recv_dataflow_signal4 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal4(
	const XrlError&	e,
	XrlArgs*	a,
	RecvDataflowSignal4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMfeaClientV0p1Client::send_recv_dataflow_signal6(
	const char*	the_tgt,
	const string&	xrl_sender_name,
	const IPv6&	source_address,
	const IPv6&	group_address,
	const uint32_t&	threshold_interval_sec,
	const uint32_t&	threshold_interval_usec,
	const uint32_t&	measured_interval_sec,
	const uint32_t&	measured_interval_usec,
	const uint32_t&	threshold_packets,
	const uint32_t&	threshold_bytes,
	const uint32_t&	measured_packets,
	const uint32_t&	measured_bytes,
	const bool&	is_threshold_in_packets,
	const bool&	is_threshold_in_bytes,
	const bool&	is_geq_upcall,
	const bool&	is_leq_upcall,
	const RecvDataflowSignal6CB&	cb
)
{
    Xrl x(the_tgt, "mfea_client/0.1/recv_dataflow_signal6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("source_address", source_address);
    x.args().add("group_address", group_address);
    x.args().add("threshold_interval_sec", threshold_interval_sec);
    x.args().add("threshold_interval_usec", threshold_interval_usec);
    x.args().add("measured_interval_sec", measured_interval_sec);
    x.args().add("measured_interval_usec", measured_interval_usec);
    x.args().add("threshold_packets", threshold_packets);
    x.args().add("threshold_bytes", threshold_bytes);
    x.args().add("measured_packets", measured_packets);
    x.args().add("measured_bytes", measured_bytes);
    x.args().add("is_threshold_in_packets", is_threshold_in_packets);
    x.args().add("is_threshold_in_bytes", is_threshold_in_bytes);
    x.args().add("is_geq_upcall", is_geq_upcall);
    x.args().add("is_leq_upcall", is_leq_upcall);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal6, cb));
}


/* Unmarshall recv_dataflow_signal6 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal6(
	const XrlError&	e,
	XrlArgs*	a,
	RecvDataflowSignal6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", (uint32_t)a->size(), 0);
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}
