//
// Created by lohse on 2/19/25.
//

#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "../UninitializedObject/UninitializedObject.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Driver/DriverDiagnostic.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/DynamicType.h"

using namespace clang;
using namespace clang::ento;
using namespace clang::ast_matchers;

class UninitializedObjectCheckerAlias : public UninitializedObjectChecker{};

void ento::registerUninitializedObjectCheckerAlias(CheckerManager &Mgr) {
  auto Chk = Mgr.registerChecker<UninitializedObjectCheckerAlias>();

  const AnalyzerOptions &AnOpts = Mgr.getAnalyzerOptions();
  UninitObjCheckerOptions &ChOpts = Chk->Opts;

  ChOpts.IsPedantic = AnOpts.getCheckerBooleanOption(Chk, "Pedantic");
  ChOpts.ShouldConvertNotesToWarnings = AnOpts.getCheckerBooleanOption(
      Chk, "NotesAsWarnings");
  ChOpts.CheckPointeeInitialization = AnOpts.getCheckerBooleanOption(
      Chk, "CheckPointeeInitialization");
  ChOpts.IgnoredRecordsWithFieldPattern =
      std::string(AnOpts.getCheckerStringOption(Chk, "IgnoreRecordsWithField"));
  ChOpts.IgnoreGuardedFields =
      AnOpts.getCheckerBooleanOption(Chk, "IgnoreGuardedFields");

  std::string ErrorMsg;
  if (!llvm::Regex(ChOpts.IgnoredRecordsWithFieldPattern).isValid(ErrorMsg))
    Mgr.reportInvalidCheckerOptionValue(Chk, "IgnoreRecordsWithField",
                                        "a valid regex, building failed with error message "
                                        "\"" + ErrorMsg + "\"");
}

bool ento::shouldRegisterUninitializedObjectCheckerAlias(const CheckerManager &mgr) {
  return true;
}
