/**************************************************************************************************
From: Solver.C -- (C) Niklas Een, Niklas Sorensson, 2004
**************************************************************************************************/

#ifndef XORSIMPLIFIER_H
#define XORSIMPLIFIER_H

#include "Solver.h"
#include "Vec.h"
#include "XSet.h"

class ClauseCleaner;

class XorSubsumer
{
public:
    
    XorSubsumer(Solver& S2);
    const bool simplifyBySubsumption(const bool doFullSubsume = false);
    void unlinkModifiedClause(vec<Lit>& origClause, XorClauseSimp c);
    void unlinkModifiedClauseNoDetachNoNULL(vec<Lit>& origClause, XorClauseSimp c);
    void unlinkClause(XorClauseSimp cc);
    XorClauseSimp linkInClause(XorClause& cl);
    void linkInAlreadyClause(XorClauseSimp& c);
    void newVar();
    
private:
    
    friend class ClauseCleaner;
    
    //Main
    vec<XorClauseSimp>        clauses;
    vec<vec<XorClauseSimp> >  occur;          // 'occur[index(lit)]' is a list of constraints containing 'lit'.
    Solver&                   solver;         // The Solver
    
    // Temporaries (to reduce allocation overhead):
    //
    vec<char>                 seen_tmp;       // (used in various places)
    
    //Start-up
    void addFromSolver(vec<XorClause*>& cs);
    void addBackToSolver();
    
    // Subsumption:
    void findSubsumed(XorClause& ps, vec<XorClauseSimp>& out_subsumed);
    void findSubsumed(const vec<Lit>& ps, const uint32_t abst, vec<XorClauseSimp>& out_subsumed);
    bool isSubsumed(XorClause& ps);
    void subsume0(XorClauseSimp& ps);
    void almost_all_database();
    template<class T1, class T2>
    bool subset(const T1& A, const T2& B);
    bool subsetAbst(uint32_t A, uint32_t B);
    void findUnMatched(vec<Lit>& A, XorClause& B, vec<Lit>& unmatchedPart);
    
    uint32_t clauses_subsumed;
    uint32_t clauses_cut;
    uint32_t origNClauses;
    uint clauseID;
};

inline bool XorSubsumer::subsetAbst(uint32_t A, uint32_t B)
{
    return !(A & ~B);
}

// Assumes 'seen' is cleared (will leave it cleared)
template<class T1, class T2>
bool XorSubsumer::subset(const T1& A, const T2& B)
{
    for (uint i = 0; i != B.size(); i++)
        seen_tmp[B[i].var()] = 1;
    for (uint i = 0; i != A.size(); i++) {
        if (!seen_tmp[A[i].var()]) {
            for (uint i = 0; i != B.size(); i++)
                seen_tmp[B[i].var()] = 0;
            return false;
        }
    }
    for (uint i = 0; i != B.size(); i++)
        seen_tmp[B[i].var()] = 0;
    return true;
}

inline void XorSubsumer::newVar()
{
    occur       .push();
    seen_tmp    .push(0);       // (one for each polarity)
}

#endif //XORSIMPLIFIER_H
