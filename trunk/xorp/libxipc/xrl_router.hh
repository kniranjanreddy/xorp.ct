// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2003 International Computer Science Institute
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

// $XORP: xorp/libxipc/xrl_router.hh,v 1.12 2003/04/02 22:58:57 hodson Exp $

#ifndef __LIBXIPC_XRL_ROUTER_HH__
#define __LIBXIPC_XRL_ROUTER_HH__

#include "config.h"
#include "libxorp/callback.hh"

#include "xrl.hh"
#include "xrl_sender.hh"
#include "xrl_cmd_map.hh"
#include "xrl_pf.hh"

class DispatchState;

class XrlCmdDispatcher : public XrlCmdMap {
public:
    XrlCmdDispatcher(const char* entity_name) : XrlCmdMap(entity_name)
    {}
    virtual ~XrlCmdDispatcher() {}
    virtual XrlError dispatch_xrl(const Xrl& xrl, XrlArgs& ret_vals) const;
};

class FinderNGClient;
class FinderNGClientXrlTarget;
class FinderNGTcpAutoConnector;
class FinderDBEntry;
class XrlRouterDispatchState;

class XrlRouter : public XrlCmdDispatcher, public XrlSender {
public:
    typedef XrlSender::Callback XrlCallback;    
    typedef XrlRouterDispatchState DispatchState;
    
public:
    XrlRouter(EventLoop&	e,
	      const char*	entity_name,
	      const char*	finder_address = "localhost",
	      uint16_t		finder_port = 0)
	throw (InvalidAddress);

    virtual ~XrlRouter();
    
    bool add_listener(XrlPFListener* listener);

    void finalize();
    
    bool connected() const;

    bool pending() const;

    bool send(const Xrl& xrl, const XrlCallback& cb);

    bool add_handler(const string& cmd, const XrlRecvCallback& rcb);

    EventLoop& eventloop() {return _e;}

protected:
    void resolve_callback(const XrlError&		e,
			  const FinderDBEntry*		dbe,
			  XrlRouterDispatchState*	ds);

    void send_callback(const XrlError&		e,
		       const Xrl&		xrl,
		       XrlArgs*			reply,
		       XrlRouterDispatchState*	ds);

    void dispose(XrlRouterDispatchState*);
    
protected:
    EventLoop&			_e;
    FinderNGClient*		_fc;
    FinderNGClientXrlTarget*	_fxt;
    FinderNGTcpAutoConnector*	_fac;
    uint32_t			_id;

    uint32_t			_rpend, _spend;

    list<XrlPFListener*>	_listeners;
    list<XrlRouterDispatchState*> _dsl;
};

#endif // __LIBXIPC_XRL_ROUTER_HH__
