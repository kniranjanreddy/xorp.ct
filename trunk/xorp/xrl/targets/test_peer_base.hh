/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/test_peer_base.hh,v 1.13 2003/11/18 01:47:43 hodson Exp $
 */


#ifndef __XRL_INTERFACES_TEST_PEER_BASE_HH__
#define __XRL_INTERFACES_TEST_PEER_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlTestPeerTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlTestPeerTargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    /**
     * Constructor.
     *
     * @param cmds an XrlCmdMap that the commands associated with the target
     *		   should be added to.  This is typically the XrlRouter
     *		   associated with the target.
     */
    XrlTestPeerTargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlTestPeerTargetBase();

    /**
     * Set command map.
     *
     * @param cmds pointer to command map to associate commands with.  This
     * argument is typically a pointer to the XrlRouter associated with the
     * target.
     *
     * @return true on success, false if cmds is null or a command map has
     * already been supplied.
     */
    bool set_command_map(XrlCmdMap* cmds);

    /**
     * Get Xrl instance name associated with command map.
     */
    inline const string& name() const { return _cmds->name(); }

    /**
     * Get version string of instance.
     */
    inline const char* version() const { return "test_peer/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Register for receiving packets and events.
     *
     *  @param genid Generation id.
     */
    virtual XrlCmdError test_peer_0_1_register(
	// Input values,
	const string&	coordinator,
	const uint32_t&	genid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Packetisation style.
     */
    virtual XrlCmdError test_peer_0_1_packetisation(
	// Input values,
	const string&	protocol) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Make a tcp connection to the specified host and port.
     *
     *  @param host name.
     *
     *  @param port number.
     */
    virtual XrlCmdError test_peer_0_1_connect(
	// Input values,
	const string&	host,
	const uint32_t&	port) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Listen for connections on this address and port.
     *
     *  @param address local address.
     *
     *  @param port local port number.
     */
    virtual XrlCmdError test_peer_0_1_listen(
	// Input values,
	const string&	address,
	const uint32_t&	port) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data Send data to the peer.
     */
    virtual XrlCmdError test_peer_0_1_send(
	// Input values,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Disconnect from the peer.
     */
    virtual XrlCmdError test_peer_0_1_disconnect() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Reset the peer. Take it back to a known state.
     */
    virtual XrlCmdError test_peer_0_1_reset() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Terminate the test peer process.
     */
    virtual XrlCmdError test_peer_0_1_terminate() = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_register(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_packetisation(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_connect(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_listen(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_send(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_disconnect(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_reset(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_test_peer_0_1_terminate(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif /* __XRL_INTERFACES_TEST_PEER_BASE_HH__ */
