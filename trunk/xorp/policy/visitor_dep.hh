// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-
// vim:set sts=4 ts=8:

// Copyright (c) 2001-2008 International Computer Science Institute
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

// $XORP: xorp/policy/visitor_setdep.hh,v 1.7 2008/01/04 03:17:13 pavlin Exp $

#ifndef __POLICY_VISITOR_DEP_HH__
#define __POLICY_VISITOR_DEP_HH__

#include <string>

#include "policy/common/policy_exception.hh"
#include "visitor.hh"
#include "set_map.hh"
#include "policy_map.hh"
#include "policy_statement.hh"
#include "node.hh"

/**
 * @short This visitor is used to check what sets a policy uses.
 *
 * This is useful for set dependancy tracking.
 */
class VisitorDep : public Visitor {
public:
    /**
     * @short Semantic error thrown if set is not found.
     */
    class sem_error : public PolicyException {
    public:
        sem_error(const char* file, size_t line, const string& init_why = "")   
            : PolicyException("sem_error", file, line, init_why) {} 
    };

    /**
     * @param setmap The setmap used.
     */
    VisitorDep(SetMap& setmap, PolicyMap& pmap);

    const Element* visit(PolicyStatement& policy);
    const Element* visit(Term& term);
    const Element* visit(NodeUn& node);
    const Element* visit(NodeBin& node);
    const Element* visit(NodeAssign& node);
    const Element* visit(NodeVar& node);
    const Element* visit(NodeSet& node);
    const Element* visit(NodeElem& node);
    const Element* visit(NodeAccept& node);
    const Element* visit(NodeReject& node);
    const Element* visit(NodeProto& node);
    const Element* visit(NodeNext& node);
    const Element* visit(NodeSubr& node);

    /**
     * @return the sets used by the policy.
     */
    const DEPS& sets() const;

private:
    void commit_deps(PolicyStatement& policy);

    SetMap&		_setmap;
    PolicyMap&		_pmap;
    DEPS		_sets;
    DEPS		_policies;
};

#endif // __POLICY_VISITOR_DEP_HH__