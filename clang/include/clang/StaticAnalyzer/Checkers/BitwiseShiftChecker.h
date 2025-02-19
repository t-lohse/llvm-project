//
// Created by lohse on 2/19/25.
//

#ifndef LLVM_BITWISESHIFTCHECKER_CPP_HPP
#define LLVM_BITWISESHIFTCHECKER_CPP_HPP

#include "clang/AST/ASTContext.h"
#include "clang/AST/CharUnits.h"
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugReporter.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/APSIntType.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ExprEngine.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/SVals.h"
#include "llvm/Support/FormatVariadic.h"
#include <memory>

using namespace clang;
using namespace ento;

class BitwiseShiftChecker : public Checker<check::PreStmt<BinaryOperator>> {
  BugType BT{this, "Bitwise shift", "Suspicious operation"};

public:
  void checkPreStmt(const BinaryOperator *B, CheckerContext &Ctx) const;

  bool Pedantic = false;
};

void ento::registerBitwiseShiftChecker(CheckerManager &Mgr);

#endif // LLVM_BITWISESHIFTCHECKER_CPP_HPP
