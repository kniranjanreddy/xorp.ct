/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/rtrmgr_base.hh,v 1.13 2004/03/09 05:51:03 mjh Exp $
 */


#ifndef __XRL_INTERFACES_RTRMGR_BASE_HH__
#define __XRL_INTERFACES_RTRMGR_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlRtrmgrTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlRtrmgrTargetBase {
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
    XrlRtrmgrTargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlRtrmgrTargetBase();

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
    inline const char* version() const { return "rtrmgr/0.0"; }

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

    virtual XrlCmdError rtrmgr_0_1_get_pid(
	// Output values,
	uint32_t&	pid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Register a user and client process with the rtrmgr.
     *
     *  @param clientname name of xrl entity supporting rtrmgr_client.xif
     *  methods.
     */
    virtual XrlCmdError rtrmgr_0_1_register_client(
	// Input values,
	const uint32_t&	userid,
	const string&	clientname,
	// Output values,
	string&	filename,
	uint32_t&	pid) = 0;

    virtual XrlCmdError rtrmgr_0_1_unregister_client(
	// Input values,
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_authenticate_client(
	// Input values,
	const uint32_t&	userid,
	const string&	clientname,
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_enter_config_mode(
	// Input values,
	const string&	token,
	const bool&	exclusive) = 0;

    virtual XrlCmdError rtrmgr_0_1_leave_config_mode(
	// Input values,
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_get_config_users(
	// Input values,
	const string&	token,
	// Output values,
	XrlAtomList&	users) = 0;

    virtual XrlCmdError rtrmgr_0_1_get_running_config(
	// Input values,
	const string&	token,
	// Output values,
	bool&	ready,
	string&	config) = 0;

    virtual XrlCmdError rtrmgr_0_1_apply_config_change(
	// Input values,
	const string&	token,
	const string&	target,
	const string&	deltas,
	const string&	deletions) = 0;

    virtual XrlCmdError rtrmgr_0_1_lock_config(
	// Input values,
	const string&	token,
	const uint32_t&	timeout,
	// Output values,
	bool&	success,
	uint32_t&	holder) = 0;

    virtual XrlCmdError rtrmgr_0_1_unlock_config(
	// Input values,
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_lock_node(
	// Input values,
	const string&	token,
	const string&	node,
	const uint32_t&	timeout,
	// Output values,
	bool&	success,
	uint32_t&	holder) = 0;

    virtual XrlCmdError rtrmgr_0_1_unlock_node(
	// Input values,
	const string&	token,
	const string&	node) = 0;

    virtual XrlCmdError rtrmgr_0_1_save_config(
	// Input values,
	const string&	token,
	const string&	filename) = 0;

    virtual XrlCmdError rtrmgr_0_1_load_config(
	// Input values,
	const string&	token,
	const string&	target,
	const string&	filename) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_get_pid(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_register_client(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_unregister_client(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_authenticate_client(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_enter_config_mode(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_leave_config_mode(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_get_config_users(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_get_running_config(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_apply_config_change(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_lock_config(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_unlock_config(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_lock_node(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_unlock_node(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_save_config(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rtrmgr_0_1_load_config(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif /* __XRL_INTERFACES_RTRMGR_BASE_HH__ */
