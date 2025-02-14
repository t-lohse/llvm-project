//
// Created by lohse on 2/13/25.
//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"

#include "../bugprone/AssignmentInIfConditionCheck.h"
#include "../bugprone/CastingThroughVoidCheck.h"
#include "../bugprone/ComparePointerToMemberVirtualFunctionCheck.h"
#include "../bugprone/CopyConstructorInitCheck.h"
#include "../bugprone/DanglingHandleCheck.h"
#include "../bugprone/ImplicitWideningOfMultiplicationResultCheck.h"
#include "../bugprone/IntegerDivisionCheck.h"
#include "../bugprone/MisplacedWideningCastCheck.h"
#include "../bugprone/MoveForwardingReferenceCheck.h"
#include "../bugprone/MultiLevelImplicitPointerConversionCheck.h"
#include "../bugprone/ParentVirtualCallCheck.h"
#include "../bugprone/UnsafeFunctionsCheck.h"
#include "../bugprone/UseAfterMoveCheck.h"

#include "../cppcoreguidelines/AvoidGotoCheck.h"
#include "../cppcoreguidelines/AvoidNonConstGlobalVariablesCheck.h"
#include "../cppcoreguidelines/InitVariablesCheck.h"
#include "../cppcoreguidelines/MissingStdForwardCheck.h"
#include "../cppcoreguidelines/NoMallocCheck.h"
#include "../cppcoreguidelines/PreferMemberInitializerCheck.h"
#include "../cppcoreguidelines/ProBoundsArrayToPointerDecayCheck.h"
#include "../cppcoreguidelines/ProBoundsConstantArrayIndexCheck.h"
#include "../cppcoreguidelines/ProBoundsPointerArithmeticCheck.h"
#include "../cppcoreguidelines/ProTypeConstCastCheck.h"
#include "../cppcoreguidelines/ProTypeCstyleCastCheck.h"
#include "../cppcoreguidelines/ProTypeMemberInitCheck.h"
#include "../cppcoreguidelines/ProTypeReinterpretCastCheck.h"
#include "../cppcoreguidelines/ProTypeStaticCastDowncastCheck.h"
#include "../cppcoreguidelines/ProTypeUnionAccessCheck.h"
#include "../cppcoreguidelines/ProTypeVarargCheck.h"
#include "../cppcoreguidelines/VirtualClassDestructorCheck.h"
#include "../fuchsia/VirtualInheritanceCheck.h"

#include "../google/IntegerTypesCheck.h"

#include "../hicpp/ExceptionBaseclassCheck.h"
#include "../hicpp/NoAssemblerCheck.h"
#include "../hicpp/SignedBitwiseCheck.h"

#include "../modernize/AvoidCArraysCheck.h"

#include "../cppcoreguidelines/AvoidNonConstGlobalVariablesCheck.h"
#include "DerefPointerCheck.h"

namespace clang::tidy {
namespace tlohse {

/// A module containing checks
class TLohseModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<DerefPointerCheck>(
        "tlohse-deref-pointer");

    // -- Bugprone alias --
    //CheckFactories.registerCheck<>("bugprone-bitwise-pointer-cast");
    CheckFactories.registerCheck<bugprone::AssignmentInIfConditionCheck>("tlohse-assignment-in-if-condition");
    CheckFactories.registerCheck<bugprone::CastingThroughVoidCheck>("tlohse-casting-through-void");
    CheckFactories.registerCheck<bugprone::ComparePointerToMemberVirtualFunctionCheck>("tlohse-compare-pointer-to-member-virtual-function");
    CheckFactories.registerCheck<bugprone::CopyConstructorInitCheck>("tlohse-copy-constructor-init");
    CheckFactories.registerCheck<bugprone::DanglingHandleCheck>("tlohse-dangling-handle");
    // candidate: easily-swappable-parameters --- Not a safety feature, but very nice
    CheckFactories.registerCheck<bugprone::ImplicitWideningOfMultiplicationResultCheck>("tlohse-implicit-widening-of-multiplication-result");
    CheckFactories.registerCheck<bugprone::IntegerDivisionCheck>("tlohse-integer-division");
    CheckFactories.registerCheck<bugprone::MisplacedWideningCastCheck>("tlohse-misplaced-widening-cast"); // DEFAULT `CheckImplicitCasts` TO TRUE
    //CheckFactories.registerCheck<bugprone::MoveForwardingReferenceCheck>("tlohse-move-forwarding-reference");
    CheckFactories.registerCheck<bugprone::MultiLevelImplicitPointerConversionCheck>("tlohse-multi-level-implicit-pointer-conversion");
    CheckFactories.registerCheck<bugprone::ParentVirtualCallCheck>("tlohse-parent-virtual-call");
    // bugprone-return-const-ref-from-parameter -- nice, but coulde be solved with borrow-checker/pointer analysis
    //CheckFactories.registerCheck<>("tlohse-tagged-union-member-count");
    CheckFactories.registerCheck<bugprone::UnsafeFunctionsCheck>("tlohse-unsafe-functions"); // ADD FUNCTIONS TO LIST! https://clang.llvm.org/extra/clang-tidy/checks/bugprone/unsafe-functions.html
    CheckFactories.registerCheck<bugprone::UseAfterMoveCheck>("tlohse-use-after-move");

    // -- C++ Core Guidelines --
    // cppcoreguidelines-avoid-const-or-ref-data-members maybe/
    CheckFactories.registerCheck<cppcoreguidelines::AvoidGotoCheck>("tlohse-avoid-goto");
    // avoid-non-const-global-variables
    CheckFactories.registerCheck<cppcoreguidelines::AvoidNonConstGlobalVariablesCheck>("tlohse-init-variables"); // Could be solved with some static analysis that checks it's initialized before usage
    CheckFactories.registerCheck<cppcoreguidelines::InitVariablesCheck>("tlohse-init-variables"); // Could be solved with some static analysis that checks it's initialized before usage
    // cppcoreguidelines-misleading-capture-default-by-value but probably just disallow capturing `this` without some explicit notion
    CheckFactories.registerCheck<cppcoreguidelines::MissingStdForwardCheck>("tlohse-missing-std-forward"); // COMPARE WITH THE FORWARDING ABOVE
    CheckFactories.registerCheck<cppcoreguidelines::NoMallocCheck>("tlohse-no-malloc");
    CheckFactories.registerCheck<cppcoreguidelines::PreferMemberInitializerCheck>("tlohse-prefer-member-initializer");
    CheckFactories.registerCheck<cppcoreguidelines::ProBoundsArrayToPointerDecayCheck>("tlohse-pro-bounds-array-to-pointer-decay");
    CheckFactories.registerCheck<cppcoreguidelines::ProBoundsConstantArrayIndexCheck>("tlohse-pro-bounds-constant-array-index");
    CheckFactories.registerCheck<cppcoreguidelines::ProBoundsPointerArithmeticCheck>("tlohse-pro-bounds-pointer-arithmetic");
    CheckFactories.registerCheck<cppcoreguidelines::ProTypeConstCastCheck>("tlohse-pro-type-const-cast");
    CheckFactories.registerCheck<cppcoreguidelines::ProTypeCstyleCastCheck>("tlohse-pro-type-cstyle-cast");
    CheckFactories.registerCheck<cppcoreguidelines::ProTypeMemberInitCheck>("tlohse-pro-type-member-init");
    CheckFactories.registerCheck<cppcoreguidelines::ProTypeReinterpretCastCheck>("tlohse-pro-type-reinterpret-cast");
    CheckFactories.registerCheck<cppcoreguidelines::ProTypeStaticCastDowncastCheck>("tlohse-pro-type-static-cast-downcast");
    CheckFactories.registerCheck<cppcoreguidelines::ProTypeUnionAccessCheck>("tlohse-pro-type-union-access");
    CheckFactories.registerCheck<cppcoreguidelines::ProTypeVarargCheck>("tlohse-pro-type-vararg");
    // cppcoreguidelines-slicing --- nice, but should not exist (inteface-only type thing)
    CheckFactories.registerCheck<cppcoreguidelines::VirtualClassDestructorCheck>("tlohse-virtual-class-destructor");

    // -- Fuchsia --
    // Maybe: fuchsia-default-arguments-calls / default-arguments-declarations -- No take on def-args currently
    CheckFactories.registerCheck<fuchsia::VirtualInheritanceCheck>("tlohse-virtual-inheritance");


    // -- Google --
    // maybe: https://clang.llvm.org/extra/clang-tidy/checks/google/explicit-constructor.html -- But kinda like implicit constructors. Maybe some operator-checks instead?
    CheckFactories.registerCheck<google::runtime::IntegerTypesCheck>("tlohse-runtime-int"); // Probably not much safety-related, but very nice!

    // -- Hi-C++ --
    CheckFactories.registerCheck<hicpp::ExceptionBaseclassCheck>("tlohse-exception-baseclass");
    CheckFactories.registerCheck<hicpp::NoAssemblerCheck>("tlohse-no-assembler");
    CheckFactories.registerCheck<hicpp::SignedBitwiseCheck>("tlohse-signed-bitwise");


    // -- Modernize --
    CheckFactories.registerCheck<modernize::AvoidCArraysCheck>("tlohse-avoid-c-arrays");


  }

  ClangTidyOptions getModuleOptions() override {
    ClangTidyOptions Options;
    ClangTidyOptions::OptionMap &Opts = Options.CheckOptions;

//    Opts["cppcoreguidelines-non-private-member-variables-in-classes."
//         "IgnoreClassesWithAllMemberVariablesBeingPublic"] = "true";

    return Options;
  }
};

// Register the LLVMTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<TLohseModule>
    X("tlohse-module", "Adds checks for the save subset of C++.");

} // namespace tlohse

// This anchor is used to force the linker to link in the generated object file
// and thus register the TLohseModule.
volatile int TLohseModuleAnchorSource = 0;

} // namespace clang::tidy
