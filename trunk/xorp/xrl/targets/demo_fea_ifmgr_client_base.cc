/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 */

#ident "$XORP: xorp/xrl/targets/demo_fea_ifmgr_client_base.cc,v 1.10 2004/04/10 07:45:13 pavlin Exp $"


#include "demo_fea_ifmgr_client_base.hh"


XrlDemoFeaIfmgrClientTargetBase::XrlDemoFeaIfmgrClientTargetBase(XrlCmdMap* cmds)
    : _cmds(cmds)
{
    if (_cmds)
	add_handlers();
}

XrlDemoFeaIfmgrClientTargetBase::~XrlDemoFeaIfmgrClientTargetBase()
{
    if (_cmds)
	remove_handlers();
}

bool
XrlDemoFeaIfmgrClientTargetBase::set_command_map(XrlCmdMap* cmds)
{
    if (_cmds == 0 && cmds) {
        _cmds = cmds;
        add_handlers();
        return true;
    }
    if (_cmds && cmds == 0) {
	remove_handlers();
        _cmds = cmds;
        return true;
    }
    return false;
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_get_target_name(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            0, (uint32_t)xa_inputs.size(), "common/0.1/get_target_name");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string name;
    try {
	XrlCmdError e = common_0_1_get_target_name(
	    name);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_target_name", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("name", name);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_get_version(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            0, (uint32_t)xa_inputs.size(), "common/0.1/get_version");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string version;
    try {
	XrlCmdError e = common_0_1_get_version(
	    version);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_version", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("version", version);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_get_status(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            0, (uint32_t)xa_inputs.size(), "common/0.1/get_status");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    uint32_t status;
    string reason;
    try {
	XrlCmdError e = common_0_1_get_status(
	    status,
	    reason);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_status", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("status", status);
	pxa_outputs->add("reason", reason);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_shutdown(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            0, (uint32_t)xa_inputs.size(), "common/0.1/shutdown");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = common_0_1_shutdown();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/shutdown", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_interface_update(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            2, (uint32_t)xa_inputs.size(), "fea_ifmgr_client/0.1/interface_update");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = fea_ifmgr_client_0_1_interface_update(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_uint32("event"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "fea_ifmgr_client/0.1/interface_update", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_vif_update(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 3) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            3, (uint32_t)xa_inputs.size(), "fea_ifmgr_client/0.1/vif_update");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = fea_ifmgr_client_0_1_vif_update(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_uint32("event"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "fea_ifmgr_client/0.1/vif_update", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_vifaddr4_update(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 4) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            4, (uint32_t)xa_inputs.size(), "fea_ifmgr_client/0.1/vifaddr4_update");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = fea_ifmgr_client_0_1_vifaddr4_update(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv4("addr"),
	    xa_inputs.get_uint32("event"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "fea_ifmgr_client/0.1/vifaddr4_update", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_vifaddr6_update(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 4) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            4, (uint32_t)xa_inputs.size(), "fea_ifmgr_client/0.1/vifaddr6_update");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = fea_ifmgr_client_0_1_vifaddr6_update(
	    xa_inputs.get_string("ifname"),
	    xa_inputs.get_string("vifname"),
	    xa_inputs.get_ipv6("addr"),
	    xa_inputs.get_uint32("event"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "fea_ifmgr_client/0.1/vifaddr6_update", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_updates_completed(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            0, (uint32_t)xa_inputs.size(), "fea_ifmgr_client/0.1/updates_completed");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = fea_ifmgr_client_0_1_updates_completed();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "fea_ifmgr_client/0.1/updates_completed", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::XrlAtomNotFound& e) {
	XLOG_ERROR("Argument not found");
	return XrlCmdError::BAD_ARGS();
    }
    return XrlCmdError::OKAY();
}

void
XrlDemoFeaIfmgrClientTargetBase::add_handlers()
{
	if (_cmds->add_handler("common/0.1/get_target_name",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "common/0.1/get_target_name");
	}
	if (_cmds->add_handler("common/0.1/get_version",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "common/0.1/get_version");
	}
	if (_cmds->add_handler("common/0.1/get_status",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_get_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "common/0.1/get_status");
	}
	if (_cmds->add_handler("common/0.1/shutdown",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_common_0_1_shutdown)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "common/0.1/shutdown");
	}
	if (_cmds->add_handler("fea_ifmgr_client/0.1/interface_update",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_interface_update)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "fea_ifmgr_client/0.1/interface_update");
	}
	if (_cmds->add_handler("fea_ifmgr_client/0.1/vif_update",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_vif_update)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "fea_ifmgr_client/0.1/vif_update");
	}
	if (_cmds->add_handler("fea_ifmgr_client/0.1/vifaddr4_update",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_vifaddr4_update)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "fea_ifmgr_client/0.1/vifaddr4_update");
	}
	if (_cmds->add_handler("fea_ifmgr_client/0.1/vifaddr6_update",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_vifaddr6_update)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "fea_ifmgr_client/0.1/vifaddr6_update");
	}
	if (_cmds->add_handler("fea_ifmgr_client/0.1/updates_completed",
	    callback(this, &XrlDemoFeaIfmgrClientTargetBase::handle_fea_ifmgr_client_0_1_updates_completed)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "demo_fea_ifmgr_client", "fea_ifmgr_client/0.1/updates_completed");
	}
	_cmds->finalize();
}

void
XrlDemoFeaIfmgrClientTargetBase::remove_handlers()
{
	_cmds->remove_handler("common/0.1/get_target_name");
	_cmds->remove_handler("common/0.1/get_version");
	_cmds->remove_handler("common/0.1/get_status");
	_cmds->remove_handler("common/0.1/shutdown");
	_cmds->remove_handler("fea_ifmgr_client/0.1/interface_update");
	_cmds->remove_handler("fea_ifmgr_client/0.1/vif_update");
	_cmds->remove_handler("fea_ifmgr_client/0.1/vifaddr4_update");
	_cmds->remove_handler("fea_ifmgr_client/0.1/vifaddr6_update");
	_cmds->remove_handler("fea_ifmgr_client/0.1/updates_completed");
}
