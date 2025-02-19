//
// Created by lohse on 2/19/25.
//

#ifndef LLVM_INNERPOINTERCHECKER_H
#define LLVM_INNERPOINTERCHECKER_H


#include "AllocationState.h"
#include "InterCheckerAPI.h"
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/BugReporter/CommonBugCategories.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallDescription.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"

using namespace clang;
using namespace ento;

class InnerPointerChecker
    : public Checker<check::DeadSymbols, check::PostCall> {

  CallDescriptionSet InvalidatingMemberFunctions{
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "append"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "assign"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "clear"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "erase"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "insert"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "pop_back"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "push_back"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "replace"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "reserve"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "resize"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "shrink_to_fit"}),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "swap"})};

  CallDescriptionSet AddressofFunctions{
      CallDescription(CDM::SimpleFunc, {"std", "addressof"}),
      CallDescription(CDM::SimpleFunc, {"std", "__addressof"})};

  CallDescriptionSet InnerPointerAccessFunctions{
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "c_str"}),
      CallDescription(CDM::SimpleFunc, {"std", "data"}, 1),
      CallDescription(CDM::CXXMethod, {"std", "basic_string", "data"})};

public:
  class InnerPointerBRVisitor : public BugReporterVisitor {
    SymbolRef PtrToBuf;

  public:
    InnerPointerBRVisitor(SymbolRef Sym) : PtrToBuf(Sym) {}

    static void *getTag() {
      static int Tag = 0;
      return &Tag;
    }

    void Profile(llvm::FoldingSetNodeID &ID) const override {
      ID.AddPointer(getTag());
    }

    PathDiagnosticPieceRef VisitNode(const ExplodedNode *N,
                                     BugReporterContext &BRC,
                                     PathSensitiveBugReport &BR) override;

    // FIXME: Scan the map once in the visitor's constructor and do a direct
    // lookup by region.
    bool isSymbolTracked(ProgramStateRef State, SymbolRef Sym);
  };

  /// Check whether the called member function potentially invalidates
  /// pointers referring to the container object's inner buffer.
  bool isInvalidatingMemberFunction(const CallEvent &Call) const;

  /// Mark pointer symbols associated with the given memory region released
  /// in the program state.
  void markPtrSymbolsReleased(const CallEvent &Call, ProgramStateRef State,
                              const MemRegion *ObjRegion,
                              CheckerContext &C) const;

  /// Standard library functions that take a non-const `basic_string` argument by
  /// reference may invalidate its inner pointers. Check for these cases and
  /// mark the pointers released.
  void checkFunctionArguments(const CallEvent &Call, ProgramStateRef State,
                              CheckerContext &C) const;

  /// Record the connection between raw pointers referring to a container
  /// object's inner buffer and the object's memory region in the program state.
  /// Mark potentially invalidated pointers released.
  void checkPostCall(const CallEvent &Call, CheckerContext &C) const;

  /// Clean up the program state map.
  void checkDeadSymbols(SymbolReaper &SymReaper, CheckerContext &C) const;
};
void ento::registerInnerPointerChecker(CheckerManager &Mgr);

#endif // LLVM_INNERPOINTERCHECKER_H
