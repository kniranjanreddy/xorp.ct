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

// $XORP: xorp/bgp/iptuple.hh,v 1.12 2006/10/27 07:14:20 atanu Exp $

#ifndef __BGP_IPTUPLE_HH__
#define __BGP_IPTUPLE_HH__

#include "bgp_module.h"
#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/ipvx.hh"

class UnresolvableHost : public XorpReasonedException {
public:
    UnresolvableHost(const char* file, size_t line, const string init_why = "")
 	: XorpReasonedException("UnresolvableHost", file, line, init_why) {}
};

class AddressFamilyMismatch : public XorpReasonedException {
public:
    AddressFamilyMismatch(const char* file, size_t line,
			  const string init_why = "")
 	: XorpReasonedException("AddressFamilyMismatch",
				file, line, init_why) {}
};

/**
 * Store the Local Interface, Local Server Port, Peer Interface and
 * Peer Server Port tuple.
 *
 * Also create the socket buffers to be used by the socket code. All the IP
 * protocol family differences can therefore be hidden in here.
 *
 * The endpoint addresses can be presented as either numeric addresses
 * or symbolic addresses. Symbolic addresses are converted to numeric
 * addresses and held as such. The symbolic address are kept to aid
 * debugging but are never accessed after the initial conversion to
 * the numeric form. Only in the constructor is there a possibility of
 * a DNS / Yellow pages interaction taking place. After this as we are
 * dealing with IP addresses there should be no danger.
 */
class Iptuple {
public:
    Iptuple();
    Iptuple(const char *local_interface, uint16_t local_port,
	    const char *peer_interface, uint16_t peer_port)
	throw(UnresolvableHost,AddressFamilyMismatch);

    Iptuple(const Iptuple&);
    Iptuple& operator=(const Iptuple&);
    void copy(const Iptuple&);

    bool operator==(const Iptuple&) const;

    const struct sockaddr *get_local_socket(size_t& len) const;
    string get_local_addr() const;
    bool get_local_addr(IPv4& addr) const;
    bool get_local_addr(IPv6& addr) const;
    uint16_t get_local_port() const;

    const struct sockaddr *get_bind_socket(size_t& len) const;

    const struct sockaddr *get_peer_socket(size_t& len) const;
    string get_peer_addr() const;
    bool get_peer_addr(IPv4& addr) const;
    bool get_peer_addr(IPv6& addr) const;
    uint16_t get_peer_port() const;

    string str() const;
private:
    void
    fill_address(const char *interface, uint16_t local_port,
		 struct sockaddr_storage& ss, size_t& len,
		 string& interface_numeric)
	throw(UnresolvableHost);

    string _local_interface;	// String representation only for debugging.
    string _peer_interface;	// String representation only for debugging.

    // For listen().
    struct sockaddr_storage	_local_sock;	 // Local socket
    size_t			_local_sock_len; // Length of local socket

    // For bind() before connect.
    struct sockaddr_storage	_bind_sock;	// Bind socket
    size_t			_bind_sock_len;	// Length of bind socket

    // For connect().
    struct sockaddr_storage	_peer_sock;	// Peer socket
    size_t			_peer_sock_len;	// Length of peer socket

    /*
    ** The local address and the peer address are stored twice once in
    ** string format and one in IPvX format. Originally the addresses
    ** were stored only as strings as they are rarely used, however
    ** the policy code may repeatedly request the peer address in IPv4
    ** or IPv6 format so keep it in the internal format for
    ** performance reasons.
    */
    string _local_address;	// Local address in numeric form
    IPvX   _local_address_ipvx;	// Local address in IPvX form
    string _peer_address;	// Peer address in numeric form
    IPvX   _peer_address_ipvx;	// Peer address in IPvX form

    /*
    ** Held in host byte order
    */
    uint16_t _local_port;	// Local port
    uint16_t _peer_port;	// Peer port
};

#endif // __BGP_IPTUPLE_HH__