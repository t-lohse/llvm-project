//
// Created by lohse on 2/13/25.
//

//===-- CppCoreGuidelinesTidyModule.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../misc/NonPrivateMemberVariablesInClassesCheck.h"
#include "../misc/UnconventionalAssignOperatorCheck.h"
#include "../modernize/AvoidCArraysCheck.h"
#include "../modernize/MacroToEnumCheck.h"
#include "../modernize/UseDefaultMemberInitCheck.h"
#include "../modernize/UseOverrideCheck.h"
#include "../performance/NoexceptDestructorCheck.h"
#include "../performance/NoexceptMoveConstructorCheck.h"
#include "../performance/NoexceptSwapCheck.h"
#include "../readability/MagicNumbersCheck.h"


#include "DerefPointerCheck.h"

namespace clang::tidy {
namespace tlohse {

/// A module containing checks of the C++ Core Guidelines
class TLohseModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<DerefPointerCheck>(
        "tlohse-deref-pointer");
  }

  ClangTidyOptions getModuleOptions() override {
    ClangTidyOptions Options;
    ClangTidyOptions::OptionMap &Opts = Options.CheckOptions;

    Opts["cppcoreguidelines-non-private-member-variables-in-classes."
         "IgnoreClassesWithAllMemberVariablesBeingPublic"] = "true";

    return Options;
  }
};

// Register the LLVMTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<TLohseModule>
    X("cppcoreguidelines-module", "Adds checks for the C++ Core Guidelines.");

} // namespace cppcoreguidelines

// This anchor is used to force the linker to link in the generated object file
// and thus register the CppCoreGuidelinesModule.
volatile int TLohseModuleAnchorSource = 0;

} // namespace clang::tidy
