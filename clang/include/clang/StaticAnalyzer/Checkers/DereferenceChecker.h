//
// Created by lohse on 2/17/25.
//

#ifndef LLVM_DEREFERENCECHECKER_H
#define LLVM_DEREFERENCECHECKER_H

#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"


namespace clang {
namespace ento {

class DereferenceChecker : public Checker< check::Location,
                                          check::Bind,
                                          EventDispatcher<ImplicitNullDerefEvent> > {
  enum DerefKind { NullPointer, UndefinedPointerValue, AddressOfLabel };

  BugType BT_Null{this, "Dereference of null pointer", categories::LogicError};
  BugType BT_Undef{this, "Dereference of undefined pointer value",
                   categories::LogicError};
  BugType BT_Label{this, "Dereference of the address of a label",
                   categories::LogicError};

  void reportBug(DerefKind K, ProgramStateRef State, const Stmt *S,
                 CheckerContext &C) const;

  bool suppressReport(CheckerContext &C, const Expr *E) const;

public:
  void checkLocation(SVal location, bool isLoad, const Stmt* S,
                     CheckerContext &C) const;
  void checkBind(SVal L, SVal V, const Stmt *S, CheckerContext &C) const;

  static void AddDerefSource(raw_ostream &os,
                             SmallVectorImpl<SourceRange> &Ranges,
                             const Expr *Ex, const ProgramState *state,
                             const LocationContext *LCtx,
                             bool loadedFrom = false);

  bool SuppressAddressSpaces = false;
};

void registerDereferenceChecker(CheckerManager &Mgr);

} // namespace ento
} // namespace clang

#endif // LLVM_DEREFERENCECHECKER_H
