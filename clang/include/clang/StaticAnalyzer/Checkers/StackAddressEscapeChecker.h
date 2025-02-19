//
// Created by lohse on 2/19/25.
//

#ifndef LLVM_STACKADDRESSESCAPECHECKER_H
#define LLVM_STACKADDRESSESCAPECHECKER_H

#include "clang/AST/ExprCXX.h"
#include "clang/Basic/SourceManager.h"
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ProgramState.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace ento;

class StackAddrEscapeChecker
    : public Checker<check::PreCall, check::PreStmt<ReturnStmt>,
                     check::EndFunction> {
  mutable IdentifierInfo *dispatch_semaphore_tII = nullptr;
  mutable std::unique_ptr<BugType> BT_stackleak;
  mutable std::unique_ptr<BugType> BT_returnstack;
  mutable std::unique_ptr<BugType> BT_capturedstackasync;
  mutable std::unique_ptr<BugType> BT_capturedstackret;

public:
  enum CheckKind {
    CK_StackAddrEscapeChecker,
    CK_StackAddrAsyncEscapeChecker,
    CK_NumCheckKinds
  };

  bool ChecksEnabled[CK_NumCheckKinds] = {false};
  CheckerNameRef CheckNames[CK_NumCheckKinds];

  void checkPreCall(const CallEvent &Call, CheckerContext &C) const;
  void checkPreStmt(const ReturnStmt *RS, CheckerContext &C) const;
  void checkEndFunction(const ReturnStmt *RS, CheckerContext &Ctx) const;

private:
  void checkReturnedBlockCaptures(const BlockDataRegion &B,
                                  CheckerContext &C) const;
  void checkAsyncExecutedBlockCaptures(const BlockDataRegion &B,
                                       CheckerContext &C) const;
  void EmitStackError(CheckerContext &C, const MemRegion *R,
                      const Expr *RetE) const;
  bool isSemaphoreCaptured(const BlockDecl &B) const;
  static SourceRange genName(raw_ostream &os, const MemRegion *R,
                             ASTContext &Ctx);
  static SmallVector<const MemRegion *, 4>
  getCapturedStackRegions(const BlockDataRegion &B, CheckerContext &C);
  static bool isNotInCurrentFrame(const MemRegion *R, CheckerContext &C);
};

void ento::registerStackAddrEscapeBase(CheckerManager &mgr);

#endif // LLVM_STACKADDRESSESCAPECHECKER_H
