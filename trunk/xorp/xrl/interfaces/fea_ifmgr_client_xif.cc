/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/fea_ifmgr_client_xif.cc,v 1.9 2004/04/10 07:42:49 pavlin Exp $"

#include "fea_ifmgr_client_xif.hh"

bool
XrlFeaIfmgrClientV0p1Client::send_interface_update(
	const char*	the_tgt,
	const string&	ifname,
	const uint32_t&	event,
	const InterfaceUpdateCB&	cb
)
{
    Xrl x(the_tgt, "fea_ifmgr_client/0.1/interface_update");
    x.args().add("ifname", ifname);
    x.args().add("event", event);
    return _sender->send(x, callback(this, &XrlFeaIfmgrClientV0p1Client::unmarshall_interface_update, cb));
}


/* Unmarshall interface_update */
void
XrlFeaIfmgrClientV0p1Client::unmarshall_interface_update(
	const XrlError&	e,
	XrlArgs*	a,
	InterfaceUpdateCB		cb
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
XrlFeaIfmgrClientV0p1Client::send_vif_update(
	const char*	the_tgt,
	const string&	ifname,
	const string&	vifname,
	const uint32_t&	event,
	const VifUpdateCB&	cb
)
{
    Xrl x(the_tgt, "fea_ifmgr_client/0.1/vif_update");
    x.args().add("ifname", ifname);
    x.args().add("vifname", vifname);
    x.args().add("event", event);
    return _sender->send(x, callback(this, &XrlFeaIfmgrClientV0p1Client::unmarshall_vif_update, cb));
}


/* Unmarshall vif_update */
void
XrlFeaIfmgrClientV0p1Client::unmarshall_vif_update(
	const XrlError&	e,
	XrlArgs*	a,
	VifUpdateCB		cb
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
XrlFeaIfmgrClientV0p1Client::send_vifaddr4_update(
	const char*	the_tgt,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	event,
	const Vifaddr4UpdateCB&	cb
)
{
    Xrl x(the_tgt, "fea_ifmgr_client/0.1/vifaddr4_update");
    x.args().add("ifname", ifname);
    x.args().add("vifname", vifname);
    x.args().add("addr", addr);
    x.args().add("event", event);
    return _sender->send(x, callback(this, &XrlFeaIfmgrClientV0p1Client::unmarshall_vifaddr4_update, cb));
}


/* Unmarshall vifaddr4_update */
void
XrlFeaIfmgrClientV0p1Client::unmarshall_vifaddr4_update(
	const XrlError&	e,
	XrlArgs*	a,
	Vifaddr4UpdateCB		cb
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
XrlFeaIfmgrClientV0p1Client::send_vifaddr6_update(
	const char*	the_tgt,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	event,
	const Vifaddr6UpdateCB&	cb
)
{
    Xrl x(the_tgt, "fea_ifmgr_client/0.1/vifaddr6_update");
    x.args().add("ifname", ifname);
    x.args().add("vifname", vifname);
    x.args().add("addr", addr);
    x.args().add("event", event);
    return _sender->send(x, callback(this, &XrlFeaIfmgrClientV0p1Client::unmarshall_vifaddr6_update, cb));
}


/* Unmarshall vifaddr6_update */
void
XrlFeaIfmgrClientV0p1Client::unmarshall_vifaddr6_update(
	const XrlError&	e,
	XrlArgs*	a,
	Vifaddr6UpdateCB		cb
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
XrlFeaIfmgrClientV0p1Client::send_updates_completed(
	const char*	the_tgt,
	const UpdatesCompletedCB&	cb
)
{
    Xrl x(the_tgt, "fea_ifmgr_client/0.1/updates_completed");
    return _sender->send(x, callback(this, &XrlFeaIfmgrClientV0p1Client::unmarshall_updates_completed, cb));
}


/* Unmarshall updates_completed */
void
XrlFeaIfmgrClientV0p1Client::unmarshall_updates_completed(
	const XrlError&	e,
	XrlArgs*	a,
	UpdatesCompletedCB		cb
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
