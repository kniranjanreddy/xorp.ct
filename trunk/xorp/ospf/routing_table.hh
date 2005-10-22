// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-
// vim:set sts=4 ts=8:

// Copyright (c) 2001-2005 International Computer Science Institute
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

// $XORP: xorp/ospf/routing_table.hh,v 1.20 2005/10/22 08:01:56 atanu Exp $

#ifndef __OSPF_ROUTING_TABLE_HH__
#define __OSPF_ROUTING_TABLE_HH__

#include <libxorp/trie.hh>

/**
 * External view of a routing entry.
 */
template <typename A>
class RouteEntry {
 public:
    /**
     * The ordering is important used to select the best route.
     */
    enum PathType {
	intra_area = 1,
	inter_area = 2,
	type1 = 3,
	type2 = 4
    };

    RouteEntry() : _destination_type(OspfTypes::Router),
		   _discard(false),
		   _address(0),
		   _id(0),
		   _area_border_router(false),
		   _as_boundary_router(false),
		   _area(0),
		   _path_type(intra_area),
		   _cost(0),
		   _type_2_cost(0),
		   _nexthop(A::ZERO()),
		   _advertising_router(0),
		   _filtered(false)
    {}

    void set_destination_type(OspfTypes::VertexType destination_type) {
	_destination_type = destination_type;
    }

    OspfTypes::VertexType get_destination_type() const {
	return _destination_type;
    }

    void set_discard(bool discard) {
	_discard = discard;
    }

    bool get_discard() const {
	return _discard;
    }

    void set_address(uint32_t address) {
	XLOG_ASSERT(OspfTypes::Network == _destination_type);
	_address = address;
    }

    uint32_t get_address() const {
	XLOG_ASSERT(OspfTypes::Network == _destination_type);
	return _address;
    }

    void set_router_id(OspfTypes::RouterID id) {
	XLOG_ASSERT(OspfTypes::Router == _destination_type);
	_id = id;
    }

    OspfTypes::RouterID get_router_id() const {
	XLOG_ASSERT(OspfTypes::Router == _destination_type);
	return _id;
    }

    void set_area_border_router(bool area_border_router) {
	XLOG_ASSERT(OspfTypes::Router == _destination_type);
	_area_border_router = area_border_router;
    }

    bool get_area_border_router() const {
	XLOG_ASSERT(OspfTypes::Router == _destination_type);
	return _area_border_router;
    }

    void set_as_boundary_router(bool as_boundary_router) {
	XLOG_ASSERT(OspfTypes::Router == _destination_type);
	_as_boundary_router = as_boundary_router;
    }

    bool get_as_boundary_router() const {
	XLOG_ASSERT(OspfTypes::Router == _destination_type);
	return _as_boundary_router;
    }

    void set_area(OspfTypes::AreaID area) {
	_area = area;
    }

    OspfTypes::AreaID get_area() const {
	return _area;
    }

    void set_path_type(PathType path_type) {
	_path_type = path_type;
    }

    PathType get_path_type() const {
	return _path_type;
    }

    void set_cost(uint32_t cost) {
	_cost = cost;
    }

    uint32_t get_cost() const {
	return _cost;
    }

    void set_type_2_cost(uint32_t type_2_cost) {
	_type_2_cost = type_2_cost;
    }

    uint32_t get_type_2_cost() const {
	return _type_2_cost;
    }

    void set_nexthop(A nexthop) {
	_nexthop = nexthop;
    }

    A get_nexthop() const {
	return _nexthop;
    }

    void set_advertising_router(uint32_t _advertising_router) {
	_advertising_router = _advertising_router;
    }

    uint32_t get_advertising_router() const {
	return _advertising_router;
    }

    void set_filtered(bool filtered) {
	_filtered = filtered;
    }

    bool get_filtered() const {
	return _filtered;
    }

    string str() {
	string output;

	output = c_format("nexthop %s metric %u", cstring(_nexthop), _cost);

	return output;
    }

 private:
    OspfTypes::VertexType _destination_type;
    bool _discard;			// True if this is a discard route.

    uint32_t _address;			// If dest type is Network

    OspfTypes:: RouterID _id;		// If dest type is Router
    bool _area_border_router;		// Only valid if dest type is router
    bool _as_boundary_router;		// Only valid if dest type is router

    OspfTypes::AreaID _area;		// Associated area.
    PathType _path_type;
    uint32_t _cost;
    uint32_t _type_2_cost;

    A _nexthop;
    uint32_t	_advertising_router;

    bool _filtered;			// True if this route has been
					// filtered by policy.
};

/**
 * Internal routing entry, potentially one per area.
 */
template <typename A>
class InternalRouteEntry {
 public:
    InternalRouteEntry() : _winner(0)
    {}

    /**
     * Add entry indexed by area.
     * @return true on sucess.
     */
    bool add_entry(OspfTypes::AreaID area, RouteEntry<A>& rt);
    
    bool replace_entry(OspfTypes::AreaID area, RouteEntry<A>& rt);
    
    /**
     * Delete entry. Perfectly safe to attempt to delete an entry for
     * an area even if no entry exists.
     *
     * @param area area ID.
     * @param winner_changed out parameter set to true if this entry
     * was the winner.
     * @return true if an entry was deleted.
     */
    bool delete_entry(OspfTypes::AreaID, bool& winner_changed);

    /**
     * Get the winning entry.
     */
    RouteEntry<A>& get_entry() const;

    /**
     * Are there any entries?
     */
    bool empty() const {
	return 0 == _winner;
    }

    string str();
 private:
    RouteEntry<A> *_winner; // Winning route.
    map<OspfTypes::AreaID, RouteEntry<A> > _entries; // Routes by area.

    bool reset_winner();
};

template <typename A>
class RoutingTable {
 public:
    RoutingTable(Ospf<A> &ospf)
	: _ospf(ospf), _in_transaction(false), _current(0), _previous(0)
    {}

    /**
     * Before [add|replace|delete]_entry can be called, this method
     * must be called to start the transaction.
     */
    void begin(OspfTypes::AreaID area);

    bool add_entry(OspfTypes::AreaID area, IPNet<A> net, RouteEntry<A>& rt);

    bool replace_entry(OspfTypes::AreaID area, IPNet<A> net,
		       RouteEntry<A>& rt);

    /**
     * Delete an entry from the current table.
     */
    bool delete_entry(OspfTypes::AreaID area, IPNet<A> net);

    /**
     * For the [add|replace|delete]_entry calls to take effect this
     * method must be called.
     */
    void end();
    
    /**
     * Lookup address A in the routing table exact match.
     *
     * @param router address being looked up.
     * @param rt if a match is found fill this in.
     * 
     * @return true if an entry is found.
     */
    bool lookup_entry(A router, RouteEntry<A>& rt);

    /**
     * Lookup network in the routing table exact match.
     *
     * @param network address being looked up.
     * @param rt if a match is found fill this in.
     * 
     * @return true if an entry is found.
     */
    bool lookup_entry(IPNet<A> net, RouteEntry<A>& rt);

    /**
     * Lookup address A in the routing table longest match.
     *
     * @param nexthop address to lookup.
     * @param rt if a match is found fill this in.
     *
     * @return true if an entry is found.
     */

    bool longest_match_entry(A router, RouteEntry<A>& rt);

    /**
     * This call notifies the routing table that this area no longer
     * exists, therefore all routes that came from this area should be
     * removed. All other areas also need to be notified so that any
     * summarisation information can be removed.
     */
    void remove_area(OspfTypes::AreaID area);

 private:
    Ospf<A>& _ospf;			// Reference to the controlling class.
    bool _in_transaction;		// Flag to verify that the
					// routing table is only
					// manipulated during a transaction.

    Trie<A, InternalRouteEntry<A> > *_current;
    Trie<A, InternalRouteEntry<A> > *_previous;


    // Yes the RouteEntry contains the area, nexthop and metric but they
    // are functionally distinct.
    bool add_route(OspfTypes::AreaID area, IPNet<A> net, A nexthop,
		   uint32_t metric, RouteEntry<A>& rt);
    bool delete_route(OspfTypes::AreaID area, IPNet<A> net, RouteEntry<A>& rt);
    bool replace_route(OspfTypes::AreaID area, IPNet<A> net, A nexthop,
		       uint32_t metric, RouteEntry<A>& rt);

    /**
     * @return true if the route should be accepted.
     */
    bool do_filtering(IPNet<A>& net, A& nexthop, uint32_t& metric,
		      RouteEntry<A>& rt);
};

#if	0
template <typename A>
class RouteEntry {
 public:
    list<A> _nexthops;		// Possible nexthops for this route

    bool _discard;		// True if this is a discard route.
    uint32_t _users;		// Only valid if this is a discard
				// route. The number of routes below
				// the discard route.
    
    OspfTypes::AreaID _area;	// Area the LSA came from.
    list<Lsa::LsaRef> lsars;	// LSAs the routes came from.
    bool _modified;		// True if this route has been
				// modified in the last sweep.
};

template <typename A>
class RoutingTable {
 public:
    RoutingTable(Ospf<A> &ospf)
	: _ospf(ospf)
    {}

    void begin();

    /**
     * Add route
     *
     * @param net network
     * @param nexthop
     * @param metric to network
     * @param equal true if this in another route to the same destination.
     */
    bool add_route(IPNet<A> net,
		   A nexthop,
		   uint32_t metric,
		   bool equal);

    /**
     * Replace route
     *
     * @param net network
     * @param nexthop
     * @param metric to network
     * @param equal true if this in another route to the same destination.
     */
    bool replace_route(IPNet<A> net,
		       A nexthop,
		       uint32_t metric,
		       bool equal);

    /**
     * Delete route
     */
    bool delete_route(IPNet<A> net);

    void end();
    
 private:
    Ospf<A>& _ospf;			// Reference to the controlling class.

    Trie<A, RouteEntry<A> > _trie;
};
#endif

#endif // __OSPF_ROUTING_TABLE_HH__
