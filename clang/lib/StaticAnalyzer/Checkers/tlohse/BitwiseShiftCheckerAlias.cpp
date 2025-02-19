//== BitwiseShiftChecker.cpp ------------------------------------*- C++ -*--==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines BitwiseShiftChecker, which is a path-sensitive checker
// that looks for undefined behavior when the operands of the bitwise shift
// operators '<<' and '>>' are invalid (negative or too large).
//
//===----------------------------------------------------------------------===//
#include "clang/StaticAnalyzer/Checkers/BitwiseShiftChecker.h"

#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ExprEngine.h"

using namespace clang;
using namespace ento;

class BitwiseShiftCheckerAlias : public BitwiseShiftChecker {
};

void ento::registerBitwiseShiftCheckerAlias(CheckerManager &Mgr) {
  auto *Chk = Mgr.registerChecker<BitwiseShiftCheckerAlias>();
  const AnalyzerOptions &Opts = Mgr.getAnalyzerOptions();
  Chk->Pedantic = Opts.getCheckerBooleanOption(Chk, "Pedantic");
}

bool ento::shouldRegisterBitwiseShiftCheckerAlias(const CheckerManager &mgr) {
  return true;
}
