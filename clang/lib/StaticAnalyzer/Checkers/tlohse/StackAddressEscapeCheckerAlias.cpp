//
// Created by lohse on 2/19/25.
//

#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Checkers/StackAddressEscapeChecker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"

using namespace clang;
using namespace ento;

class StackAddrEscapeCheckerAlias
    : public StackAddrEscapeChecker{};


void ento::registerStackAddrEscapeCheckerAlias(CheckerManager &Mgr) {
  StackAddrEscapeChecker *Chk = Mgr.getChecker<StackAddrEscapeChecker>();
  Chk->ChecksEnabled[StackAddrEscapeChecker::CK_StackAddrEscapeChecker] = true;
  Chk->CheckNames[StackAddrEscapeChecker::CK_StackAddrEscapeChecker] =
      Mgr.getCurrentCheckerName();
}

bool ento::shouldRegisterStackAddrEscapeCheckerAlias(const CheckerManager &mgr) { return true; }
