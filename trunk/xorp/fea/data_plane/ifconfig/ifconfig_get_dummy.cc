// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2007 International Computer Science Institute
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

#ident "$XORP: xorp/fea/forwarding_plane/ifconfig/ifconfig_get_dummy.cc,v 1.2 2007/04/26 06:29:46 pavlin Exp $"

#include "fea/fea_module.h"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"

#include "fea/ifconfig.hh"
#include "fea/ifconfig_get.hh"


//
// Get information about network interfaces from the underlying system.
//
// The mechanism to obtain the information is dummy (for testing purpose).
//


IfConfigGetDummy::IfConfigGetDummy(IfConfig& ifconfig)
    : IfConfigGet(ifconfig)
{
#if 0	// XXX: by default Dummy is never registering by itself
    register_ifconfig_primary();
#endif
}

IfConfigGetDummy::~IfConfigGetDummy()
{
    string error_msg;

    if (stop(error_msg) != XORP_OK) {
	XLOG_ERROR("Cannot stop the dummy mechanism to get "
		   "information about network interfaces from the underlying "
		   "system: %s",
		   error_msg.c_str());
    }
}

int
IfConfigGetDummy::start(string& error_msg)
{
    UNUSED(error_msg);

    if (_is_running)
	return (XORP_OK);

    _is_running = true;

    return (XORP_OK);
}

int
IfConfigGetDummy::stop(string& error_msg)
{
    UNUSED(error_msg);

    if (! _is_running)
	return (XORP_OK);

    _is_running = false;

    return (XORP_OK);
}

bool
IfConfigGetDummy::pull_config(IfTree& iftree)
{
    iftree = ifconfig().live_config();
    
    return true;
}