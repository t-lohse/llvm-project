set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  Support
  )

add_clang_library(clangTidyTLohseModule
 # AvoidCapturingLambdaCoroutinesCheck.cpp
 # AvoidConstOrRefDataMembersCheck.cpp
 # AvoidDoWhileCheck.cpp
 # AvoidGotoCheck.cpp
 # AvoidNonConstGlobalVariablesCheck.cpp
 # AvoidReferenceCoroutineParametersCheck.cpp
 # CppCoreGuidelinesTidyModule.cpp
 # InitVariablesCheck.cpp
 # InterfacesGlobalInitCheck.cpp
 # MacroUsageCheck.cpp
 # MisleadingCaptureDefaultByValueCheck.cpp
 # MissingStdForwardCheck.cpp
 # NarrowingConversionsCheck.cpp
 # NoMallocCheck.cpp
 # NoSuspendWithLockCheck.cpp
 # OwningMemoryCheck.cpp
 # PreferMemberInitializerCheck.cpp
 # ProBoundsArrayToPointerDecayCheck.cpp
 # ProBoundsConstantArrayIndexCheck.cpp
 # ProBoundsPointerArithmeticCheck.cpp
 # ProTypeConstCastCheck.cpp
 # ProTypeCstyleCastCheck.cpp
 # ProTypeMemberInitCheck.cpp
 # ProTypeReinterpretCastCheck.cpp
 # ProTypeStaticCastDowncastCheck.cpp
 # ProTypeUnionAccessCheck.cpp
 # ProTypeVarargCheck.cpp
 # RvalueReferenceParamNotMovedCheck.cpp
 # SlicingCheck.cpp
 # SpecialMemberFunctionsCheck.cpp
 # VirtualClassDestructorCheck.cpp
        DerefPointerCheck.cpp
        TLohseTidyModule.cpp

  LINK_LIBS
  clangTidy
  clangTidyMiscModule
  clangTidyModernizeModule
  clangTidyPerformanceModule
  clangTidyReadabilityModule
  clangTidyUtils

  DEPENDS
  omp_gen
  ClangDriverOptions
  )

clang_target_link_libraries(clangTidyTLohseModule
  PRIVATE
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangSerialization
  clangTooling
  )
