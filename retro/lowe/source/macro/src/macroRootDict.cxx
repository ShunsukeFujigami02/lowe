// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIrhomedIfujigamidIretrodIlowedIsourcedImacrodIsrcdImacroRootDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/rhome/fujigami/retro/lowe/source/macro/include/eventdisplay.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/goodness_data.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/likelihood_direction_data.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizedData.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/CSearch_range.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/C4Number.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/FileList.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/efficiency.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/HistByTree.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/HistError.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/HistBias.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AngleRange.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Thitinfo.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/TReconstructdata.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfunction.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tafunction.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tdistance_function.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tlikelihood.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_dir_i.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_i_func.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Ttof.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodnessdirection.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/TOption_minimize.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodness.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfsumgoodness.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/BiasError.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/FileManager.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizeTag.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizeManager.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizeFile.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/TNinWater.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Eventdisplay(void *p = 0);
   static void *newArray_Eventdisplay(Long_t size, void *p);
   static void delete_Eventdisplay(void *p);
   static void deleteArray_Eventdisplay(void *p);
   static void destruct_Eventdisplay(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Eventdisplay*)
   {
      ::Eventdisplay *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Eventdisplay >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Eventdisplay", ::Eventdisplay::Class_Version(), "", 10,
                  typeid(::Eventdisplay), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Eventdisplay::Dictionary, isa_proxy, 4,
                  sizeof(::Eventdisplay) );
      instance.SetNew(&new_Eventdisplay);
      instance.SetNewArray(&newArray_Eventdisplay);
      instance.SetDelete(&delete_Eventdisplay);
      instance.SetDeleteArray(&deleteArray_Eventdisplay);
      instance.SetDestructor(&destruct_Eventdisplay);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Eventdisplay*)
   {
      return GenerateInitInstanceLocal((::Eventdisplay*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Eventdisplay*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_goodness_data(void *p = 0);
   static void *newArray_goodness_data(Long_t size, void *p);
   static void delete_goodness_data(void *p);
   static void deleteArray_goodness_data(void *p);
   static void destruct_goodness_data(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::goodness_data*)
   {
      ::goodness_data *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::goodness_data >(0);
      static ::ROOT::TGenericClassInfo 
         instance("goodness_data", ::goodness_data::Class_Version(), "", 8,
                  typeid(::goodness_data), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::goodness_data::Dictionary, isa_proxy, 4,
                  sizeof(::goodness_data) );
      instance.SetNew(&new_goodness_data);
      instance.SetNewArray(&newArray_goodness_data);
      instance.SetDelete(&delete_goodness_data);
      instance.SetDeleteArray(&deleteArray_goodness_data);
      instance.SetDestructor(&destruct_goodness_data);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::goodness_data*)
   {
      return GenerateInitInstanceLocal((::goodness_data*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::goodness_data*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_l_dir_data(void *p = 0);
   static void *newArray_l_dir_data(Long_t size, void *p);
   static void delete_l_dir_data(void *p);
   static void deleteArray_l_dir_data(void *p);
   static void destruct_l_dir_data(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::l_dir_data*)
   {
      ::l_dir_data *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::l_dir_data >(0);
      static ::ROOT::TGenericClassInfo 
         instance("l_dir_data", ::l_dir_data::Class_Version(), "", 6,
                  typeid(::l_dir_data), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::l_dir_data::Dictionary, isa_proxy, 4,
                  sizeof(::l_dir_data) );
      instance.SetNew(&new_l_dir_data);
      instance.SetNewArray(&newArray_l_dir_data);
      instance.SetDelete(&delete_l_dir_data);
      instance.SetDeleteArray(&deleteArray_l_dir_data);
      instance.SetDestructor(&destruct_l_dir_data);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::l_dir_data*)
   {
      return GenerateInitInstanceLocal((::l_dir_data*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::l_dir_data*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AnalizedData(void *p = 0);
   static void *newArray_AnalizedData(Long_t size, void *p);
   static void delete_AnalizedData(void *p);
   static void deleteArray_AnalizedData(void *p);
   static void destruct_AnalizedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AnalizedData*)
   {
      ::AnalizedData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AnalizedData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AnalizedData", ::AnalizedData::Class_Version(), "", 11,
                  typeid(::AnalizedData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AnalizedData::Dictionary, isa_proxy, 4,
                  sizeof(::AnalizedData) );
      instance.SetNew(&new_AnalizedData);
      instance.SetNewArray(&newArray_AnalizedData);
      instance.SetDelete(&delete_AnalizedData);
      instance.SetDeleteArray(&deleteArray_AnalizedData);
      instance.SetDestructor(&destruct_AnalizedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AnalizedData*)
   {
      return GenerateInitInstanceLocal((::AnalizedData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::AnalizedData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_C4Number(void *p = 0);
   static void *newArray_C4Number(Long_t size, void *p);
   static void delete_C4Number(void *p);
   static void deleteArray_C4Number(void *p);
   static void destruct_C4Number(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::C4Number*)
   {
      ::C4Number *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::C4Number >(0);
      static ::ROOT::TGenericClassInfo 
         instance("C4Number", ::C4Number::Class_Version(), "", 6,
                  typeid(::C4Number), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::C4Number::Dictionary, isa_proxy, 4,
                  sizeof(::C4Number) );
      instance.SetNew(&new_C4Number);
      instance.SetNewArray(&newArray_C4Number);
      instance.SetDelete(&delete_C4Number);
      instance.SetDeleteArray(&deleteArray_C4Number);
      instance.SetDestructor(&destruct_C4Number);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::C4Number*)
   {
      return GenerateInitInstanceLocal((::C4Number*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::C4Number*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CSearch_range(void *p = 0);
   static void *newArray_CSearch_range(Long_t size, void *p);
   static void delete_CSearch_range(void *p);
   static void deleteArray_CSearch_range(void *p);
   static void destruct_CSearch_range(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CSearch_range*)
   {
      ::CSearch_range *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CSearch_range >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CSearch_range", ::CSearch_range::Class_Version(), "", 11,
                  typeid(::CSearch_range), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CSearch_range::Dictionary, isa_proxy, 4,
                  sizeof(::CSearch_range) );
      instance.SetNew(&new_CSearch_range);
      instance.SetNewArray(&newArray_CSearch_range);
      instance.SetDelete(&delete_CSearch_range);
      instance.SetDeleteArray(&deleteArray_CSearch_range);
      instance.SetDestructor(&destruct_CSearch_range);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CSearch_range*)
   {
      return GenerateInitInstanceLocal((::CSearch_range*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CSearch_range*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FileList(void *p = 0);
   static void *newArray_FileList(Long_t size, void *p);
   static void delete_FileList(void *p);
   static void deleteArray_FileList(void *p);
   static void destruct_FileList(void *p);
   static Long64_t merge_FileList(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FileList*)
   {
      ::FileList *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FileList >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FileList", ::FileList::Class_Version(), "", 11,
                  typeid(::FileList), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FileList::Dictionary, isa_proxy, 4,
                  sizeof(::FileList) );
      instance.SetNew(&new_FileList);
      instance.SetNewArray(&newArray_FileList);
      instance.SetDelete(&delete_FileList);
      instance.SetDeleteArray(&deleteArray_FileList);
      instance.SetDestructor(&destruct_FileList);
      instance.SetMerge(&merge_FileList);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FileList*)
   {
      return GenerateInitInstanceLocal((::FileList*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FileList*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_efficiency(void *p = 0);
   static void *newArray_efficiency(Long_t size, void *p);
   static void delete_efficiency(void *p);
   static void deleteArray_efficiency(void *p);
   static void destruct_efficiency(void *p);
   static void directoryAutoAdd_efficiency(void *obj, TDirectory *dir);
   static Long64_t merge_efficiency(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::efficiency*)
   {
      ::efficiency *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::efficiency >(0);
      static ::ROOT::TGenericClassInfo 
         instance("efficiency", ::efficiency::Class_Version(), "", 8,
                  typeid(::efficiency), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::efficiency::Dictionary, isa_proxy, 4,
                  sizeof(::efficiency) );
      instance.SetNew(&new_efficiency);
      instance.SetNewArray(&newArray_efficiency);
      instance.SetDelete(&delete_efficiency);
      instance.SetDeleteArray(&deleteArray_efficiency);
      instance.SetDestructor(&destruct_efficiency);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_efficiency);
      instance.SetMerge(&merge_efficiency);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::efficiency*)
   {
      return GenerateInitInstanceLocal((::efficiency*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::efficiency*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH1DByTree(void *p = 0);
   static void *newArray_TH1DByTree(Long_t size, void *p);
   static void delete_TH1DByTree(void *p);
   static void deleteArray_TH1DByTree(void *p);
   static void destruct_TH1DByTree(void *p);
   static void directoryAutoAdd_TH1DByTree(void *obj, TDirectory *dir);
   static Long64_t merge_TH1DByTree(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH1DByTree*)
   {
      ::TH1DByTree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH1DByTree >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TH1DByTree", ::TH1DByTree::Class_Version(), "", 11,
                  typeid(::TH1DByTree), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH1DByTree::Dictionary, isa_proxy, 4,
                  sizeof(::TH1DByTree) );
      instance.SetNew(&new_TH1DByTree);
      instance.SetNewArray(&newArray_TH1DByTree);
      instance.SetDelete(&delete_TH1DByTree);
      instance.SetDeleteArray(&deleteArray_TH1DByTree);
      instance.SetDestructor(&destruct_TH1DByTree);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_TH1DByTree);
      instance.SetMerge(&merge_TH1DByTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH1DByTree*)
   {
      return GenerateInitInstanceLocal((::TH1DByTree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TH1DByTree*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HistError(void *p = 0);
   static void *newArray_HistError(Long_t size, void *p);
   static void delete_HistError(void *p);
   static void deleteArray_HistError(void *p);
   static void destruct_HistError(void *p);
   static void directoryAutoAdd_HistError(void *obj, TDirectory *dir);
   static Long64_t merge_HistError(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HistError*)
   {
      ::HistError *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HistError >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HistError", ::HistError::Class_Version(), "", 9,
                  typeid(::HistError), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HistError::Dictionary, isa_proxy, 4,
                  sizeof(::HistError) );
      instance.SetNew(&new_HistError);
      instance.SetNewArray(&newArray_HistError);
      instance.SetDelete(&delete_HistError);
      instance.SetDeleteArray(&deleteArray_HistError);
      instance.SetDestructor(&destruct_HistError);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_HistError);
      instance.SetMerge(&merge_HistError);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HistError*)
   {
      return GenerateInitInstanceLocal((::HistError*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HistError*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HistBias(void *p = 0);
   static void *newArray_HistBias(Long_t size, void *p);
   static void delete_HistBias(void *p);
   static void deleteArray_HistBias(void *p);
   static void destruct_HistBias(void *p);
   static void directoryAutoAdd_HistBias(void *obj, TDirectory *dir);
   static Long64_t merge_HistBias(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HistBias*)
   {
      ::HistBias *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HistBias >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HistBias", ::HistBias::Class_Version(), "", 9,
                  typeid(::HistBias), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HistBias::Dictionary, isa_proxy, 4,
                  sizeof(::HistBias) );
      instance.SetNew(&new_HistBias);
      instance.SetNewArray(&newArray_HistBias);
      instance.SetDelete(&delete_HistBias);
      instance.SetDeleteArray(&deleteArray_HistBias);
      instance.SetDestructor(&destruct_HistBias);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_HistBias);
      instance.SetMerge(&merge_HistBias);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HistBias*)
   {
      return GenerateInitInstanceLocal((::HistBias*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HistBias*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AngleRange(void *p = 0);
   static void *newArray_AngleRange(Long_t size, void *p);
   static void delete_AngleRange(void *p);
   static void deleteArray_AngleRange(void *p);
   static void destruct_AngleRange(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AngleRange*)
   {
      ::AngleRange *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AngleRange >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AngleRange", ::AngleRange::Class_Version(), "", 7,
                  typeid(::AngleRange), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AngleRange::Dictionary, isa_proxy, 4,
                  sizeof(::AngleRange) );
      instance.SetNew(&new_AngleRange);
      instance.SetNewArray(&newArray_AngleRange);
      instance.SetDelete(&delete_AngleRange);
      instance.SetDeleteArray(&deleteArray_AngleRange);
      instance.SetDestructor(&destruct_AngleRange);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AngleRange*)
   {
      return GenerateInitInstanceLocal((::AngleRange*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::AngleRange*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Thitinfo(void *p = 0);
   static void *newArray_Thitinfo(Long_t size, void *p);
   static void delete_Thitinfo(void *p);
   static void deleteArray_Thitinfo(void *p);
   static void destruct_Thitinfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Thitinfo*)
   {
      ::Thitinfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Thitinfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Thitinfo", ::Thitinfo::Class_Version(), "", 12,
                  typeid(::Thitinfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Thitinfo::Dictionary, isa_proxy, 4,
                  sizeof(::Thitinfo) );
      instance.SetNew(&new_Thitinfo);
      instance.SetNewArray(&newArray_Thitinfo);
      instance.SetDelete(&delete_Thitinfo);
      instance.SetDeleteArray(&deleteArray_Thitinfo);
      instance.SetDestructor(&destruct_Thitinfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Thitinfo*)
   {
      return GenerateInitInstanceLocal((::Thitinfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Thitinfo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TReconstructdata(void *p = 0);
   static void *newArray_TReconstructdata(Long_t size, void *p);
   static void delete_TReconstructdata(void *p);
   static void deleteArray_TReconstructdata(void *p);
   static void destruct_TReconstructdata(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TReconstructdata*)
   {
      ::TReconstructdata *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TReconstructdata >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TReconstructdata", ::TReconstructdata::Class_Version(), "", 13,
                  typeid(::TReconstructdata), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TReconstructdata::Dictionary, isa_proxy, 4,
                  sizeof(::TReconstructdata) );
      instance.SetNew(&new_TReconstructdata);
      instance.SetNewArray(&newArray_TReconstructdata);
      instance.SetDelete(&delete_TReconstructdata);
      instance.SetDeleteArray(&deleteArray_TReconstructdata);
      instance.SetDestructor(&destruct_TReconstructdata);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TReconstructdata*)
   {
      return GenerateInitInstanceLocal((::TReconstructdata*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TReconstructdata*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TReconstructdata_minimize(void *p = 0);
   static void *newArray_TReconstructdata_minimize(Long_t size, void *p);
   static void delete_TReconstructdata_minimize(void *p);
   static void deleteArray_TReconstructdata_minimize(void *p);
   static void destruct_TReconstructdata_minimize(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TReconstructdata_minimize*)
   {
      ::TReconstructdata_minimize *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TReconstructdata_minimize >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TReconstructdata_minimize", ::TReconstructdata_minimize::Class_Version(), "", 98,
                  typeid(::TReconstructdata_minimize), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TReconstructdata_minimize::Dictionary, isa_proxy, 4,
                  sizeof(::TReconstructdata_minimize) );
      instance.SetNew(&new_TReconstructdata_minimize);
      instance.SetNewArray(&newArray_TReconstructdata_minimize);
      instance.SetDelete(&delete_TReconstructdata_minimize);
      instance.SetDeleteArray(&deleteArray_TReconstructdata_minimize);
      instance.SetDestructor(&destruct_TReconstructdata_minimize);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TReconstructdata_minimize*)
   {
      return GenerateInitInstanceLocal((::TReconstructdata_minimize*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TReconstructdata_minimize*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TReconstructhit(void *p = 0);
   static void *newArray_TReconstructhit(Long_t size, void *p);
   static void delete_TReconstructhit(void *p);
   static void deleteArray_TReconstructhit(void *p);
   static void destruct_TReconstructhit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TReconstructhit*)
   {
      ::TReconstructhit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TReconstructhit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TReconstructhit", ::TReconstructhit::Class_Version(), "", 166,
                  typeid(::TReconstructhit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TReconstructhit::Dictionary, isa_proxy, 4,
                  sizeof(::TReconstructhit) );
      instance.SetNew(&new_TReconstructhit);
      instance.SetNewArray(&newArray_TReconstructhit);
      instance.SetDelete(&delete_TReconstructhit);
      instance.SetDeleteArray(&deleteArray_TReconstructhit);
      instance.SetDestructor(&destruct_TReconstructhit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TReconstructhit*)
   {
      return GenerateInitInstanceLocal((::TReconstructhit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TReconstructhit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Tfunction(void *p);
   static void deleteArray_Tfunction(void *p);
   static void destruct_Tfunction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfunction*)
   {
      ::Tfunction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfunction >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfunction", ::Tfunction::Class_Version(), "", 9,
                  typeid(::Tfunction), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfunction::Dictionary, isa_proxy, 4,
                  sizeof(::Tfunction) );
      instance.SetDelete(&delete_Tfunction);
      instance.SetDeleteArray(&deleteArray_Tfunction);
      instance.SetDestructor(&destruct_Tfunction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfunction*)
   {
      return GenerateInitInstanceLocal((::Tfunction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfunction*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Tafunction(void *p);
   static void deleteArray_Tafunction(void *p);
   static void destruct_Tafunction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tafunction*)
   {
      ::Tafunction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tafunction >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tafunction", ::Tafunction::Class_Version(), "", 8,
                  typeid(::Tafunction), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tafunction::Dictionary, isa_proxy, 4,
                  sizeof(::Tafunction) );
      instance.SetDelete(&delete_Tafunction);
      instance.SetDeleteArray(&deleteArray_Tafunction);
      instance.SetDestructor(&destruct_Tafunction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tafunction*)
   {
      return GenerateInitInstanceLocal((::Tafunction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tafunction*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tafuncprototype(void *p = 0);
   static void *newArray_Tafuncprototype(Long_t size, void *p);
   static void delete_Tafuncprototype(void *p);
   static void deleteArray_Tafuncprototype(void *p);
   static void destruct_Tafuncprototype(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tafuncprototype*)
   {
      ::Tafuncprototype *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tafuncprototype >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tafuncprototype", ::Tafuncprototype::Class_Version(), "", 34,
                  typeid(::Tafuncprototype), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tafuncprototype::Dictionary, isa_proxy, 4,
                  sizeof(::Tafuncprototype) );
      instance.SetNew(&new_Tafuncprototype);
      instance.SetNewArray(&newArray_Tafuncprototype);
      instance.SetDelete(&delete_Tafuncprototype);
      instance.SetDeleteArray(&deleteArray_Tafuncprototype);
      instance.SetDestructor(&destruct_Tafuncprototype);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tafuncprototype*)
   {
      return GenerateInitInstanceLocal((::Tafuncprototype*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tafuncprototype*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Tdistance_function(void *p);
   static void deleteArray_Tdistance_function(void *p);
   static void destruct_Tdistance_function(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tdistance_function*)
   {
      ::Tdistance_function *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tdistance_function >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tdistance_function", ::Tdistance_function::Class_Version(), "", 9,
                  typeid(::Tdistance_function), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tdistance_function::Dictionary, isa_proxy, 4,
                  sizeof(::Tdistance_function) );
      instance.SetDelete(&delete_Tdistance_function);
      instance.SetDeleteArray(&deleteArray_Tdistance_function);
      instance.SetDestructor(&destruct_Tdistance_function);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tdistance_function*)
   {
      return GenerateInitInstanceLocal((::Tdistance_function*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tdistance_function*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tdistance_position_pmt(void *p = 0);
   static void *newArray_Tdistance_position_pmt(Long_t size, void *p);
   static void delete_Tdistance_position_pmt(void *p);
   static void deleteArray_Tdistance_position_pmt(void *p);
   static void destruct_Tdistance_position_pmt(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tdistance_position_pmt*)
   {
      ::Tdistance_position_pmt *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tdistance_position_pmt >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tdistance_position_pmt", ::Tdistance_position_pmt::Class_Version(), "", 34,
                  typeid(::Tdistance_position_pmt), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tdistance_position_pmt::Dictionary, isa_proxy, 4,
                  sizeof(::Tdistance_position_pmt) );
      instance.SetNew(&new_Tdistance_position_pmt);
      instance.SetNewArray(&newArray_Tdistance_position_pmt);
      instance.SetDelete(&delete_Tdistance_position_pmt);
      instance.SetDeleteArray(&deleteArray_Tdistance_position_pmt);
      instance.SetDestructor(&destruct_Tdistance_position_pmt);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tdistance_position_pmt*)
   {
      return GenerateInitInstanceLocal((::Tdistance_position_pmt*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tdistance_position_pmt*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tdistance_position_retro(void *p = 0);
   static void *newArray_Tdistance_position_retro(Long_t size, void *p);
   static void delete_Tdistance_position_retro(void *p);
   static void deleteArray_Tdistance_position_retro(void *p);
   static void destruct_Tdistance_position_retro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tdistance_position_retro*)
   {
      ::Tdistance_position_retro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tdistance_position_retro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tdistance_position_retro", ::Tdistance_position_retro::Class_Version(), "", 46,
                  typeid(::Tdistance_position_retro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tdistance_position_retro::Dictionary, isa_proxy, 4,
                  sizeof(::Tdistance_position_retro) );
      instance.SetNew(&new_Tdistance_position_retro);
      instance.SetNewArray(&newArray_Tdistance_position_retro);
      instance.SetDelete(&delete_Tdistance_position_retro);
      instance.SetDeleteArray(&deleteArray_Tdistance_position_retro);
      instance.SetDestructor(&destruct_Tdistance_position_retro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tdistance_position_retro*)
   {
      return GenerateInitInstanceLocal((::Tdistance_position_retro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tdistance_position_retro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tdistance_fly_retro(void *p = 0);
   static void *newArray_Tdistance_fly_retro(Long_t size, void *p);
   static void delete_Tdistance_fly_retro(void *p);
   static void deleteArray_Tdistance_fly_retro(void *p);
   static void destruct_Tdistance_fly_retro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tdistance_fly_retro*)
   {
      ::Tdistance_fly_retro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tdistance_fly_retro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tdistance_fly_retro", ::Tdistance_fly_retro::Class_Version(), "", 62,
                  typeid(::Tdistance_fly_retro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tdistance_fly_retro::Dictionary, isa_proxy, 4,
                  sizeof(::Tdistance_fly_retro) );
      instance.SetNew(&new_Tdistance_fly_retro);
      instance.SetNewArray(&newArray_Tdistance_fly_retro);
      instance.SetDelete(&delete_Tdistance_fly_retro);
      instance.SetDeleteArray(&deleteArray_Tdistance_fly_retro);
      instance.SetDestructor(&destruct_Tdistance_fly_retro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tdistance_fly_retro*)
   {
      return GenerateInitInstanceLocal((::Tdistance_fly_retro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tdistance_fly_retro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Tfdirection(void *p);
   static void deleteArray_Tfdirection(void *p);
   static void destruct_Tfdirection(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfdirection*)
   {
      ::Tfdirection *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfdirection >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfdirection", ::Tfdirection::Class_Version(), "", 8,
                  typeid(::Tfdirection), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfdirection::Dictionary, isa_proxy, 4,
                  sizeof(::Tfdirection) );
      instance.SetDelete(&delete_Tfdirection);
      instance.SetDeleteArray(&deleteArray_Tfdirection);
      instance.SetDestructor(&destruct_Tfdirection);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfdirection*)
   {
      return GenerateInitInstanceLocal((::Tfdirection*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfdirection*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfdirprototypenoretro(void *p = 0);
   static void *newArray_Tfdirprototypenoretro(Long_t size, void *p);
   static void delete_Tfdirprototypenoretro(void *p);
   static void deleteArray_Tfdirprototypenoretro(void *p);
   static void destruct_Tfdirprototypenoretro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfdirprototypenoretro*)
   {
      ::Tfdirprototypenoretro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfdirprototypenoretro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfdirprototypenoretro", ::Tfdirprototypenoretro::Class_Version(), "", 35,
                  typeid(::Tfdirprototypenoretro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfdirprototypenoretro::Dictionary, isa_proxy, 4,
                  sizeof(::Tfdirprototypenoretro) );
      instance.SetNew(&new_Tfdirprototypenoretro);
      instance.SetNewArray(&newArray_Tfdirprototypenoretro);
      instance.SetDelete(&delete_Tfdirprototypenoretro);
      instance.SetDeleteArray(&deleteArray_Tfdirprototypenoretro);
      instance.SetDestructor(&destruct_Tfdirprototypenoretro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfdirprototypenoretro*)
   {
      return GenerateInitInstanceLocal((::Tfdirprototypenoretro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfdirprototypenoretro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfdirprototypeonretro(void *p = 0);
   static void *newArray_Tfdirprototypeonretro(Long_t size, void *p);
   static void delete_Tfdirprototypeonretro(void *p);
   static void deleteArray_Tfdirprototypeonretro(void *p);
   static void destruct_Tfdirprototypeonretro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfdirprototypeonretro*)
   {
      ::Tfdirprototypeonretro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfdirprototypeonretro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfdirprototypeonretro", ::Tfdirprototypeonretro::Class_Version(), "", 44,
                  typeid(::Tfdirprototypeonretro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfdirprototypeonretro::Dictionary, isa_proxy, 4,
                  sizeof(::Tfdirprototypeonretro) );
      instance.SetNew(&new_Tfdirprototypeonretro);
      instance.SetNewArray(&newArray_Tfdirprototypeonretro);
      instance.SetDelete(&delete_Tfdirprototypeonretro);
      instance.SetDeleteArray(&deleteArray_Tfdirprototypeonretro);
      instance.SetDestructor(&destruct_Tfdirprototypeonretro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfdirprototypeonretro*)
   {
      return GenerateInitInstanceLocal((::Tfdirprototypeonretro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfdirprototypeonretro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfdirbydatanoretro(void *p = 0);
   static void *newArray_Tfdirbydatanoretro(Long_t size, void *p);
   static void delete_Tfdirbydatanoretro(void *p);
   static void deleteArray_Tfdirbydatanoretro(void *p);
   static void destruct_Tfdirbydatanoretro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfdirbydatanoretro*)
   {
      ::Tfdirbydatanoretro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfdirbydatanoretro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfdirbydatanoretro", ::Tfdirbydatanoretro::Class_Version(), "", 53,
                  typeid(::Tfdirbydatanoretro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfdirbydatanoretro::Dictionary, isa_proxy, 4,
                  sizeof(::Tfdirbydatanoretro) );
      instance.SetNew(&new_Tfdirbydatanoretro);
      instance.SetNewArray(&newArray_Tfdirbydatanoretro);
      instance.SetDelete(&delete_Tfdirbydatanoretro);
      instance.SetDeleteArray(&deleteArray_Tfdirbydatanoretro);
      instance.SetDestructor(&destruct_Tfdirbydatanoretro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfdirbydatanoretro*)
   {
      return GenerateInitInstanceLocal((::Tfdirbydatanoretro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfdirbydatanoretro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfdirbydataonretro(void *p = 0);
   static void *newArray_Tfdirbydataonretro(Long_t size, void *p);
   static void delete_Tfdirbydataonretro(void *p);
   static void deleteArray_Tfdirbydataonretro(void *p);
   static void destruct_Tfdirbydataonretro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfdirbydataonretro*)
   {
      ::Tfdirbydataonretro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfdirbydataonretro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfdirbydataonretro", ::Tfdirbydataonretro::Class_Version(), "", 63,
                  typeid(::Tfdirbydataonretro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfdirbydataonretro::Dictionary, isa_proxy, 4,
                  sizeof(::Tfdirbydataonretro) );
      instance.SetNew(&new_Tfdirbydataonretro);
      instance.SetNewArray(&newArray_Tfdirbydataonretro);
      instance.SetDelete(&delete_Tfdirbydataonretro);
      instance.SetDeleteArray(&deleteArray_Tfdirbydataonretro);
      instance.SetDestructor(&destruct_Tfdirbydataonretro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfdirbydataonretro*)
   {
      return GenerateInitInstanceLocal((::Tfdirbydataonretro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfdirbydataonretro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Tlikelihood(void *p);
   static void deleteArray_Tlikelihood(void *p);
   static void destruct_Tlikelihood(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tlikelihood*)
   {
      ::Tlikelihood *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tlikelihood >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tlikelihood", ::Tlikelihood::Class_Version(), "", 13,
                  typeid(::Tlikelihood), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tlikelihood::Dictionary, isa_proxy, 4,
                  sizeof(::Tlikelihood) );
      instance.SetDelete(&delete_Tlikelihood);
      instance.SetDeleteArray(&deleteArray_Tlikelihood);
      instance.SetDestructor(&destruct_Tlikelihood);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tlikelihood*)
   {
      return GenerateInitInstanceLocal((::Tlikelihood*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tlikelihood*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tlikelihoodnoretro(void *p = 0);
   static void *newArray_Tlikelihoodnoretro(Long_t size, void *p);
   static void delete_Tlikelihoodnoretro(void *p);
   static void deleteArray_Tlikelihoodnoretro(void *p);
   static void destruct_Tlikelihoodnoretro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tlikelihoodnoretro*)
   {
      ::Tlikelihoodnoretro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tlikelihoodnoretro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tlikelihoodnoretro", ::Tlikelihoodnoretro::Class_Version(), "", 60,
                  typeid(::Tlikelihoodnoretro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tlikelihoodnoretro::Dictionary, isa_proxy, 4,
                  sizeof(::Tlikelihoodnoretro) );
      instance.SetNew(&new_Tlikelihoodnoretro);
      instance.SetNewArray(&newArray_Tlikelihoodnoretro);
      instance.SetDelete(&delete_Tlikelihoodnoretro);
      instance.SetDeleteArray(&deleteArray_Tlikelihoodnoretro);
      instance.SetDestructor(&destruct_Tlikelihoodnoretro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tlikelihoodnoretro*)
   {
      return GenerateInitInstanceLocal((::Tlikelihoodnoretro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tlikelihoodnoretro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tlikelihoodonretro(void *p = 0);
   static void *newArray_Tlikelihoodonretro(Long_t size, void *p);
   static void delete_Tlikelihoodonretro(void *p);
   static void deleteArray_Tlikelihoodonretro(void *p);
   static void destruct_Tlikelihoodonretro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tlikelihoodonretro*)
   {
      ::Tlikelihoodonretro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tlikelihoodonretro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tlikelihoodonretro", ::Tlikelihoodonretro::Class_Version(), "", 70,
                  typeid(::Tlikelihoodonretro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tlikelihoodonretro::Dictionary, isa_proxy, 4,
                  sizeof(::Tlikelihoodonretro) );
      instance.SetNew(&new_Tlikelihoodonretro);
      instance.SetNewArray(&newArray_Tlikelihoodonretro);
      instance.SetDelete(&delete_Tlikelihoodonretro);
      instance.SetDeleteArray(&deleteArray_Tlikelihoodonretro);
      instance.SetDestructor(&destruct_Tlikelihoodonretro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tlikelihoodonretro*)
   {
      return GenerateInitInstanceLocal((::Tlikelihoodonretro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tlikelihoodonretro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tlikelihoodsum(void *p = 0);
   static void *newArray_Tlikelihoodsum(Long_t size, void *p);
   static void delete_Tlikelihoodsum(void *p);
   static void deleteArray_Tlikelihoodsum(void *p);
   static void destruct_Tlikelihoodsum(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tlikelihoodsum*)
   {
      ::Tlikelihoodsum *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tlikelihoodsum >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tlikelihoodsum", ::Tlikelihoodsum::Class_Version(), "", 80,
                  typeid(::Tlikelihoodsum), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tlikelihoodsum::Dictionary, isa_proxy, 4,
                  sizeof(::Tlikelihoodsum) );
      instance.SetNew(&new_Tlikelihoodsum);
      instance.SetNewArray(&newArray_Tlikelihoodsum);
      instance.SetDelete(&delete_Tlikelihoodsum);
      instance.SetDeleteArray(&deleteArray_Tlikelihoodsum);
      instance.SetDestructor(&destruct_Tlikelihoodsum);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tlikelihoodsum*)
   {
      return GenerateInitInstanceLocal((::Tlikelihoodsum*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tlikelihoodsum*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Ttheta_dir_i(void *p = 0);
   static void *newArray_Ttheta_dir_i(Long_t size, void *p);
   static void delete_Ttheta_dir_i(void *p);
   static void deleteArray_Ttheta_dir_i(void *p);
   static void destruct_Ttheta_dir_i(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Ttheta_dir_i*)
   {
      ::Ttheta_dir_i *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Ttheta_dir_i >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Ttheta_dir_i", ::Ttheta_dir_i::Class_Version(), "", 9,
                  typeid(::Ttheta_dir_i), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Ttheta_dir_i::Dictionary, isa_proxy, 4,
                  sizeof(::Ttheta_dir_i) );
      instance.SetNew(&new_Ttheta_dir_i);
      instance.SetNewArray(&newArray_Ttheta_dir_i);
      instance.SetDelete(&delete_Ttheta_dir_i);
      instance.SetDeleteArray(&deleteArray_Ttheta_dir_i);
      instance.SetDestructor(&destruct_Ttheta_dir_i);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Ttheta_dir_i*)
   {
      return GenerateInitInstanceLocal((::Ttheta_dir_i*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Ttheta_dir_i*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Ttheta_i_func(void *p = 0);
   static void *newArray_Ttheta_i_func(Long_t size, void *p);
   static void delete_Ttheta_i_func(void *p);
   static void deleteArray_Ttheta_i_func(void *p);
   static void destruct_Ttheta_i_func(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Ttheta_i_func*)
   {
      ::Ttheta_i_func *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Ttheta_i_func >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Ttheta_i_func", ::Ttheta_i_func::Class_Version(), "", 11,
                  typeid(::Ttheta_i_func), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Ttheta_i_func::Dictionary, isa_proxy, 4,
                  sizeof(::Ttheta_i_func) );
      instance.SetNew(&new_Ttheta_i_func);
      instance.SetNewArray(&newArray_Ttheta_i_func);
      instance.SetDelete(&delete_Ttheta_i_func);
      instance.SetDeleteArray(&deleteArray_Ttheta_i_func);
      instance.SetDestructor(&destruct_Ttheta_i_func);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Ttheta_i_func*)
   {
      return GenerateInitInstanceLocal((::Ttheta_i_func*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Ttheta_i_func*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Ttof(void *p = 0);
   static void *newArray_Ttof(Long_t size, void *p);
   static void delete_Ttof(void *p);
   static void deleteArray_Ttof(void *p);
   static void destruct_Ttof(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Ttof*)
   {
      ::Ttof *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Ttof >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Ttof", ::Ttof::Class_Version(), "", 13,
                  typeid(::Ttof), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Ttof::Dictionary, isa_proxy, 4,
                  sizeof(::Ttof) );
      instance.SetNew(&new_Ttof);
      instance.SetNewArray(&newArray_Ttof);
      instance.SetDelete(&delete_Ttof);
      instance.SetDeleteArray(&deleteArray_Ttof);
      instance.SetDestructor(&destruct_Ttof);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Ttof*)
   {
      return GenerateInitInstanceLocal((::Ttof*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Ttof*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfgoodnessdirection(void *p = 0);
   static void *newArray_Tfgoodnessdirection(Long_t size, void *p);
   static void delete_Tfgoodnessdirection(void *p);
   static void deleteArray_Tfgoodnessdirection(void *p);
   static void destruct_Tfgoodnessdirection(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfgoodnessdirection*)
   {
      ::Tfgoodnessdirection *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfgoodnessdirection >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfgoodnessdirection", ::Tfgoodnessdirection::Class_Version(), "", 6,
                  typeid(::Tfgoodnessdirection), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfgoodnessdirection::Dictionary, isa_proxy, 4,
                  sizeof(::Tfgoodnessdirection) );
      instance.SetNew(&new_Tfgoodnessdirection);
      instance.SetNewArray(&newArray_Tfgoodnessdirection);
      instance.SetDelete(&delete_Tfgoodnessdirection);
      instance.SetDeleteArray(&deleteArray_Tfgoodnessdirection);
      instance.SetDestructor(&destruct_Tfgoodnessdirection);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfgoodnessdirection*)
   {
      return GenerateInitInstanceLocal((::Tfgoodnessdirection*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfgoodnessdirection*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TOption_minimize(void *p = 0);
   static void *newArray_TOption_minimize(Long_t size, void *p);
   static void delete_TOption_minimize(void *p);
   static void deleteArray_TOption_minimize(void *p);
   static void destruct_TOption_minimize(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TOption_minimize*)
   {
      ::TOption_minimize *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TOption_minimize >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TOption_minimize", ::TOption_minimize::Class_Version(), "", 7,
                  typeid(::TOption_minimize), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TOption_minimize::Dictionary, isa_proxy, 4,
                  sizeof(::TOption_minimize) );
      instance.SetNew(&new_TOption_minimize);
      instance.SetNewArray(&newArray_TOption_minimize);
      instance.SetDelete(&delete_TOption_minimize);
      instance.SetDeleteArray(&deleteArray_TOption_minimize);
      instance.SetDestructor(&destruct_TOption_minimize);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TOption_minimize*)
   {
      return GenerateInitInstanceLocal((::TOption_minimize*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TOption_minimize*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfgoodness(void *p = 0);
   static void *newArray_Tfgoodness(Long_t size, void *p);
   static void delete_Tfgoodness(void *p);
   static void deleteArray_Tfgoodness(void *p);
   static void destruct_Tfgoodness(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfgoodness*)
   {
      ::Tfgoodness *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfgoodness >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfgoodness", ::Tfgoodness::Class_Version(), "", 8,
                  typeid(::Tfgoodness), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfgoodness::Dictionary, isa_proxy, 4,
                  sizeof(::Tfgoodness) );
      instance.SetNew(&new_Tfgoodness);
      instance.SetNewArray(&newArray_Tfgoodness);
      instance.SetDelete(&delete_Tfgoodness);
      instance.SetDeleteArray(&deleteArray_Tfgoodness);
      instance.SetDestructor(&destruct_Tfgoodness);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfgoodness*)
   {
      return GenerateInitInstanceLocal((::Tfgoodness*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfgoodness*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Tfsumgoodness(void *p);
   static void deleteArray_Tfsumgoodness(void *p);
   static void destruct_Tfsumgoodness(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfsumgoodness*)
   {
      ::Tfsumgoodness *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfsumgoodness >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfsumgoodness", ::Tfsumgoodness::Class_Version(), "", 6,
                  typeid(::Tfsumgoodness), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfsumgoodness::Dictionary, isa_proxy, 4,
                  sizeof(::Tfsumgoodness) );
      instance.SetDelete(&delete_Tfsumgoodness);
      instance.SetDeleteArray(&deleteArray_Tfsumgoodness);
      instance.SetDestructor(&destruct_Tfsumgoodness);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfsumgoodness*)
   {
      return GenerateInitInstanceLocal((::Tfsumgoodness*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfsumgoodness*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfsumgoodnessnoretro(void *p = 0);
   static void *newArray_Tfsumgoodnessnoretro(Long_t size, void *p);
   static void delete_Tfsumgoodnessnoretro(void *p);
   static void deleteArray_Tfsumgoodnessnoretro(void *p);
   static void destruct_Tfsumgoodnessnoretro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfsumgoodnessnoretro*)
   {
      ::Tfsumgoodnessnoretro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfsumgoodnessnoretro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfsumgoodnessnoretro", ::Tfsumgoodnessnoretro::Class_Version(), "", 43,
                  typeid(::Tfsumgoodnessnoretro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfsumgoodnessnoretro::Dictionary, isa_proxy, 4,
                  sizeof(::Tfsumgoodnessnoretro) );
      instance.SetNew(&new_Tfsumgoodnessnoretro);
      instance.SetNewArray(&newArray_Tfsumgoodnessnoretro);
      instance.SetDelete(&delete_Tfsumgoodnessnoretro);
      instance.SetDeleteArray(&deleteArray_Tfsumgoodnessnoretro);
      instance.SetDestructor(&destruct_Tfsumgoodnessnoretro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfsumgoodnessnoretro*)
   {
      return GenerateInitInstanceLocal((::Tfsumgoodnessnoretro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfsumgoodnessnoretro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Tfsumgoodnesssum(void *p = 0);
   static void *newArray_Tfsumgoodnesssum(Long_t size, void *p);
   static void delete_Tfsumgoodnesssum(void *p);
   static void deleteArray_Tfsumgoodnesssum(void *p);
   static void destruct_Tfsumgoodnesssum(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Tfsumgoodnesssum*)
   {
      ::Tfsumgoodnesssum *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Tfsumgoodnesssum >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Tfsumgoodnesssum", ::Tfsumgoodnesssum::Class_Version(), "", 57,
                  typeid(::Tfsumgoodnesssum), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Tfsumgoodnesssum::Dictionary, isa_proxy, 4,
                  sizeof(::Tfsumgoodnesssum) );
      instance.SetNew(&new_Tfsumgoodnesssum);
      instance.SetNewArray(&newArray_Tfsumgoodnesssum);
      instance.SetDelete(&delete_Tfsumgoodnesssum);
      instance.SetDeleteArray(&deleteArray_Tfsumgoodnesssum);
      instance.SetDestructor(&destruct_Tfsumgoodnesssum);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Tfsumgoodnesssum*)
   {
      return GenerateInitInstanceLocal((::Tfsumgoodnesssum*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Tfsumgoodnesssum*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_BiasError(void *p = 0);
   static void *newArray_BiasError(Long_t size, void *p);
   static void delete_BiasError(void *p);
   static void deleteArray_BiasError(void *p);
   static void destruct_BiasError(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BiasError*)
   {
      ::BiasError *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BiasError >(0);
      static ::ROOT::TGenericClassInfo 
         instance("BiasError", ::BiasError::Class_Version(), "", 6,
                  typeid(::BiasError), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BiasError::Dictionary, isa_proxy, 4,
                  sizeof(::BiasError) );
      instance.SetNew(&new_BiasError);
      instance.SetNewArray(&newArray_BiasError);
      instance.SetDelete(&delete_BiasError);
      instance.SetDeleteArray(&deleteArray_BiasError);
      instance.SetDestructor(&destruct_BiasError);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BiasError*)
   {
      return GenerateInitInstanceLocal((::BiasError*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BiasError*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AnalizeTag(void *p = 0);
   static void *newArray_AnalizeTag(Long_t size, void *p);
   static void delete_AnalizeTag(void *p);
   static void deleteArray_AnalizeTag(void *p);
   static void destruct_AnalizeTag(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AnalizeTag*)
   {
      ::AnalizeTag *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AnalizeTag >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AnalizeTag", ::AnalizeTag::Class_Version(), "", 7,
                  typeid(::AnalizeTag), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AnalizeTag::Dictionary, isa_proxy, 4,
                  sizeof(::AnalizeTag) );
      instance.SetNew(&new_AnalizeTag);
      instance.SetNewArray(&newArray_AnalizeTag);
      instance.SetDelete(&delete_AnalizeTag);
      instance.SetDeleteArray(&deleteArray_AnalizeTag);
      instance.SetDestructor(&destruct_AnalizeTag);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AnalizeTag*)
   {
      return GenerateInitInstanceLocal((::AnalizeTag*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::AnalizeTag*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AnalizeFile(void *p = 0);
   static void *newArray_AnalizeFile(Long_t size, void *p);
   static void delete_AnalizeFile(void *p);
   static void deleteArray_AnalizeFile(void *p);
   static void destruct_AnalizeFile(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AnalizeFile*)
   {
      ::AnalizeFile *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AnalizeFile >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AnalizeFile", ::AnalizeFile::Class_Version(), "", 15,
                  typeid(::AnalizeFile), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AnalizeFile::Dictionary, isa_proxy, 4,
                  sizeof(::AnalizeFile) );
      instance.SetNew(&new_AnalizeFile);
      instance.SetNewArray(&newArray_AnalizeFile);
      instance.SetDelete(&delete_AnalizeFile);
      instance.SetDeleteArray(&deleteArray_AnalizeFile);
      instance.SetDestructor(&destruct_AnalizeFile);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AnalizeFile*)
   {
      return GenerateInitInstanceLocal((::AnalizeFile*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::AnalizeFile*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FileManager(void *p = 0);
   static void *newArray_FileManager(Long_t size, void *p);
   static void delete_FileManager(void *p);
   static void deleteArray_FileManager(void *p);
   static void destruct_FileManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FileManager*)
   {
      ::FileManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FileManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FileManager", ::FileManager::Class_Version(), "", 15,
                  typeid(::FileManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FileManager::Dictionary, isa_proxy, 4,
                  sizeof(::FileManager) );
      instance.SetNew(&new_FileManager);
      instance.SetNewArray(&newArray_FileManager);
      instance.SetDelete(&delete_FileManager);
      instance.SetDeleteArray(&deleteArray_FileManager);
      instance.SetDestructor(&destruct_FileManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FileManager*)
   {
      return GenerateInitInstanceLocal((::FileManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FileManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AnalizeManager(void *p = 0);
   static void *newArray_AnalizeManager(Long_t size, void *p);
   static void delete_AnalizeManager(void *p);
   static void deleteArray_AnalizeManager(void *p);
   static void destruct_AnalizeManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AnalizeManager*)
   {
      ::AnalizeManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AnalizeManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AnalizeManager", ::AnalizeManager::Class_Version(), "", 16,
                  typeid(::AnalizeManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AnalizeManager::Dictionary, isa_proxy, 4,
                  sizeof(::AnalizeManager) );
      instance.SetNew(&new_AnalizeManager);
      instance.SetNewArray(&newArray_AnalizeManager);
      instance.SetDelete(&delete_AnalizeManager);
      instance.SetDeleteArray(&deleteArray_AnalizeManager);
      instance.SetDestructor(&destruct_AnalizeManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AnalizeManager*)
   {
      return GenerateInitInstanceLocal((::AnalizeManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::AnalizeManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNinWater(void *p = 0);
   static void *newArray_TNinWater(Long_t size, void *p);
   static void delete_TNinWater(void *p);
   static void deleteArray_TNinWater(void *p);
   static void destruct_TNinWater(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNinWater*)
   {
      ::TNinWater *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNinWater >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TNinWater", ::TNinWater::Class_Version(), "", 6,
                  typeid(::TNinWater), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNinWater::Dictionary, isa_proxy, 4,
                  sizeof(::TNinWater) );
      instance.SetNew(&new_TNinWater);
      instance.SetNewArray(&newArray_TNinWater);
      instance.SetDelete(&delete_TNinWater);
      instance.SetDeleteArray(&deleteArray_TNinWater);
      instance.SetDestructor(&destruct_TNinWater);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNinWater*)
   {
      return GenerateInitInstanceLocal((::TNinWater*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TNinWater*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Eventdisplay::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Eventdisplay::Class_Name()
{
   return "Eventdisplay";
}

//______________________________________________________________________________
const char *Eventdisplay::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Eventdisplay*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Eventdisplay::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Eventdisplay*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Eventdisplay::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Eventdisplay*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Eventdisplay::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Eventdisplay*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr goodness_data::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *goodness_data::Class_Name()
{
   return "goodness_data";
}

//______________________________________________________________________________
const char *goodness_data::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::goodness_data*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int goodness_data::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::goodness_data*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *goodness_data::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::goodness_data*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *goodness_data::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::goodness_data*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr l_dir_data::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *l_dir_data::Class_Name()
{
   return "l_dir_data";
}

//______________________________________________________________________________
const char *l_dir_data::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::l_dir_data*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int l_dir_data::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::l_dir_data*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *l_dir_data::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::l_dir_data*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *l_dir_data::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::l_dir_data*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AnalizedData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AnalizedData::Class_Name()
{
   return "AnalizedData";
}

//______________________________________________________________________________
const char *AnalizedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizedData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AnalizedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizedData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AnalizedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizedData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AnalizedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizedData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr C4Number::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *C4Number::Class_Name()
{
   return "C4Number";
}

//______________________________________________________________________________
const char *C4Number::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::C4Number*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int C4Number::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::C4Number*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *C4Number::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::C4Number*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *C4Number::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::C4Number*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CSearch_range::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CSearch_range::Class_Name()
{
   return "CSearch_range";
}

//______________________________________________________________________________
const char *CSearch_range::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CSearch_range*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CSearch_range::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CSearch_range*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CSearch_range::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CSearch_range*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CSearch_range::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CSearch_range*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FileList::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FileList::Class_Name()
{
   return "FileList";
}

//______________________________________________________________________________
const char *FileList::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FileList*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FileList::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FileList*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FileList::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FileList*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FileList::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FileList*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr efficiency::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *efficiency::Class_Name()
{
   return "efficiency";
}

//______________________________________________________________________________
const char *efficiency::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::efficiency*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int efficiency::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::efficiency*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *efficiency::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::efficiency*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *efficiency::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::efficiency*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH1DByTree::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TH1DByTree::Class_Name()
{
   return "TH1DByTree";
}

//______________________________________________________________________________
const char *TH1DByTree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1DByTree*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TH1DByTree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1DByTree*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH1DByTree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1DByTree*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH1DByTree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1DByTree*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HistError::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HistError::Class_Name()
{
   return "HistError";
}

//______________________________________________________________________________
const char *HistError::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistError*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HistError::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistError*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HistError::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistError*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HistError::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistError*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HistBias::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HistBias::Class_Name()
{
   return "HistBias";
}

//______________________________________________________________________________
const char *HistBias::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistBias*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HistBias::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistBias*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HistBias::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistBias*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HistBias::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistBias*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AngleRange::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AngleRange::Class_Name()
{
   return "AngleRange";
}

//______________________________________________________________________________
const char *AngleRange::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AngleRange*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AngleRange::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AngleRange*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AngleRange::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AngleRange*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AngleRange::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AngleRange*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Thitinfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Thitinfo::Class_Name()
{
   return "Thitinfo";
}

//______________________________________________________________________________
const char *Thitinfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Thitinfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Thitinfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Thitinfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Thitinfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Thitinfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Thitinfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Thitinfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TReconstructdata::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TReconstructdata::Class_Name()
{
   return "TReconstructdata";
}

//______________________________________________________________________________
const char *TReconstructdata::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TReconstructdata::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TReconstructdata::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TReconstructdata::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TReconstructdata_minimize::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TReconstructdata_minimize::Class_Name()
{
   return "TReconstructdata_minimize";
}

//______________________________________________________________________________
const char *TReconstructdata_minimize::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata_minimize*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TReconstructdata_minimize::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata_minimize*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TReconstructdata_minimize::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata_minimize*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TReconstructdata_minimize::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TReconstructdata_minimize*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TReconstructhit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TReconstructhit::Class_Name()
{
   return "TReconstructhit";
}

//______________________________________________________________________________
const char *TReconstructhit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TReconstructhit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TReconstructhit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TReconstructhit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TReconstructhit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TReconstructhit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TReconstructhit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TReconstructhit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfunction::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfunction::Class_Name()
{
   return "Tfunction";
}

//______________________________________________________________________________
const char *Tfunction::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfunction*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfunction::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfunction*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfunction::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfunction*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfunction::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfunction*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tafunction::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tafunction::Class_Name()
{
   return "Tafunction";
}

//______________________________________________________________________________
const char *Tafunction::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tafunction*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tafunction::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tafunction*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tafunction::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tafunction*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tafunction::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tafunction*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tafuncprototype::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tafuncprototype::Class_Name()
{
   return "Tafuncprototype";
}

//______________________________________________________________________________
const char *Tafuncprototype::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tafuncprototype*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tafuncprototype::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tafuncprototype*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tafuncprototype::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tafuncprototype*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tafuncprototype::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tafuncprototype*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tdistance_function::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tdistance_function::Class_Name()
{
   return "Tdistance_function";
}

//______________________________________________________________________________
const char *Tdistance_function::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_function*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tdistance_function::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_function*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tdistance_function::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_function*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tdistance_function::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_function*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tdistance_position_pmt::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tdistance_position_pmt::Class_Name()
{
   return "Tdistance_position_pmt";
}

//______________________________________________________________________________
const char *Tdistance_position_pmt::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_pmt*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tdistance_position_pmt::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_pmt*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tdistance_position_pmt::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_pmt*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tdistance_position_pmt::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_pmt*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tdistance_position_retro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tdistance_position_retro::Class_Name()
{
   return "Tdistance_position_retro";
}

//______________________________________________________________________________
const char *Tdistance_position_retro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_retro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tdistance_position_retro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_retro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tdistance_position_retro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_retro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tdistance_position_retro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_position_retro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tdistance_fly_retro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tdistance_fly_retro::Class_Name()
{
   return "Tdistance_fly_retro";
}

//______________________________________________________________________________
const char *Tdistance_fly_retro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_fly_retro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tdistance_fly_retro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_fly_retro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tdistance_fly_retro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_fly_retro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tdistance_fly_retro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tdistance_fly_retro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfdirection::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfdirection::Class_Name()
{
   return "Tfdirection";
}

//______________________________________________________________________________
const char *Tfdirection::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirection*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfdirection::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirection*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfdirection::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirection*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfdirection::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirection*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfdirprototypenoretro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfdirprototypenoretro::Class_Name()
{
   return "Tfdirprototypenoretro";
}

//______________________________________________________________________________
const char *Tfdirprototypenoretro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypenoretro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfdirprototypenoretro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypenoretro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfdirprototypenoretro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypenoretro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfdirprototypenoretro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypenoretro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfdirprototypeonretro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfdirprototypeonretro::Class_Name()
{
   return "Tfdirprototypeonretro";
}

//______________________________________________________________________________
const char *Tfdirprototypeonretro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypeonretro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfdirprototypeonretro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypeonretro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfdirprototypeonretro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypeonretro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfdirprototypeonretro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirprototypeonretro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfdirbydatanoretro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfdirbydatanoretro::Class_Name()
{
   return "Tfdirbydatanoretro";
}

//______________________________________________________________________________
const char *Tfdirbydatanoretro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydatanoretro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfdirbydatanoretro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydatanoretro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfdirbydatanoretro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydatanoretro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfdirbydatanoretro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydatanoretro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfdirbydataonretro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfdirbydataonretro::Class_Name()
{
   return "Tfdirbydataonretro";
}

//______________________________________________________________________________
const char *Tfdirbydataonretro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydataonretro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfdirbydataonretro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydataonretro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfdirbydataonretro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydataonretro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfdirbydataonretro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfdirbydataonretro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tlikelihood::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tlikelihood::Class_Name()
{
   return "Tlikelihood";
}

//______________________________________________________________________________
const char *Tlikelihood::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihood*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tlikelihood::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihood*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tlikelihood::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihood*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tlikelihood::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihood*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tlikelihoodnoretro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tlikelihoodnoretro::Class_Name()
{
   return "Tlikelihoodnoretro";
}

//______________________________________________________________________________
const char *Tlikelihoodnoretro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodnoretro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tlikelihoodnoretro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodnoretro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tlikelihoodnoretro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodnoretro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tlikelihoodnoretro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodnoretro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tlikelihoodonretro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tlikelihoodonretro::Class_Name()
{
   return "Tlikelihoodonretro";
}

//______________________________________________________________________________
const char *Tlikelihoodonretro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodonretro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tlikelihoodonretro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodonretro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tlikelihoodonretro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodonretro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tlikelihoodonretro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodonretro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tlikelihoodsum::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tlikelihoodsum::Class_Name()
{
   return "Tlikelihoodsum";
}

//______________________________________________________________________________
const char *Tlikelihoodsum::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodsum*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tlikelihoodsum::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodsum*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tlikelihoodsum::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodsum*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tlikelihoodsum::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tlikelihoodsum*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Ttheta_dir_i::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Ttheta_dir_i::Class_Name()
{
   return "Ttheta_dir_i";
}

//______________________________________________________________________________
const char *Ttheta_dir_i::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_dir_i*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Ttheta_dir_i::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_dir_i*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Ttheta_dir_i::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_dir_i*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Ttheta_dir_i::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_dir_i*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Ttheta_i_func::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Ttheta_i_func::Class_Name()
{
   return "Ttheta_i_func";
}

//______________________________________________________________________________
const char *Ttheta_i_func::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_i_func*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Ttheta_i_func::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_i_func*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Ttheta_i_func::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_i_func*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Ttheta_i_func::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ttheta_i_func*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Ttof::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Ttof::Class_Name()
{
   return "Ttof";
}

//______________________________________________________________________________
const char *Ttof::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ttof*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Ttof::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ttof*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Ttof::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ttof*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Ttof::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ttof*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfgoodnessdirection::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfgoodnessdirection::Class_Name()
{
   return "Tfgoodnessdirection";
}

//______________________________________________________________________________
const char *Tfgoodnessdirection::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodnessdirection*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfgoodnessdirection::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodnessdirection*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfgoodnessdirection::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodnessdirection*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfgoodnessdirection::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodnessdirection*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TOption_minimize::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TOption_minimize::Class_Name()
{
   return "TOption_minimize";
}

//______________________________________________________________________________
const char *TOption_minimize::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOption_minimize*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TOption_minimize::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOption_minimize*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TOption_minimize::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOption_minimize*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TOption_minimize::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOption_minimize*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfgoodness::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfgoodness::Class_Name()
{
   return "Tfgoodness";
}

//______________________________________________________________________________
const char *Tfgoodness::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodness*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfgoodness::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodness*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfgoodness::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodness*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfgoodness::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfgoodness*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfsumgoodness::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfsumgoodness::Class_Name()
{
   return "Tfsumgoodness";
}

//______________________________________________________________________________
const char *Tfsumgoodness::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodness*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfsumgoodness::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodness*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfsumgoodness::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodness*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfsumgoodness::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodness*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfsumgoodnessnoretro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfsumgoodnessnoretro::Class_Name()
{
   return "Tfsumgoodnessnoretro";
}

//______________________________________________________________________________
const char *Tfsumgoodnessnoretro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnessnoretro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfsumgoodnessnoretro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnessnoretro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfsumgoodnessnoretro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnessnoretro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfsumgoodnessnoretro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnessnoretro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Tfsumgoodnesssum::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tfsumgoodnesssum::Class_Name()
{
   return "Tfsumgoodnesssum";
}

//______________________________________________________________________________
const char *Tfsumgoodnesssum::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnesssum*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tfsumgoodnesssum::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnesssum*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tfsumgoodnesssum::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnesssum*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tfsumgoodnesssum::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Tfsumgoodnesssum*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BiasError::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BiasError::Class_Name()
{
   return "BiasError";
}

//______________________________________________________________________________
const char *BiasError::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BiasError*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BiasError::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BiasError*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BiasError::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BiasError*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BiasError::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BiasError*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AnalizeTag::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AnalizeTag::Class_Name()
{
   return "AnalizeTag";
}

//______________________________________________________________________________
const char *AnalizeTag::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizeTag*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AnalizeTag::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizeTag*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AnalizeTag::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizeTag*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AnalizeTag::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizeTag*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AnalizeFile::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AnalizeFile::Class_Name()
{
   return "AnalizeFile";
}

//______________________________________________________________________________
const char *AnalizeFile::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizeFile*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AnalizeFile::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizeFile*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AnalizeFile::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizeFile*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AnalizeFile::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizeFile*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FileManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FileManager::Class_Name()
{
   return "FileManager";
}

//______________________________________________________________________________
const char *FileManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FileManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FileManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FileManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FileManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FileManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FileManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FileManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AnalizeManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AnalizeManager::Class_Name()
{
   return "AnalizeManager";
}

//______________________________________________________________________________
const char *AnalizeManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizeManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AnalizeManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AnalizeManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AnalizeManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizeManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AnalizeManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AnalizeManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNinWater::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNinWater::Class_Name()
{
   return "TNinWater";
}

//______________________________________________________________________________
const char *TNinWater::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNinWater*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNinWater::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNinWater*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNinWater::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNinWater*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNinWater::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNinWater*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Eventdisplay::Streamer(TBuffer &R__b)
{
   // Stream an object of class Eventdisplay.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Eventdisplay::Class(),this);
   } else {
      R__b.WriteClassBuffer(Eventdisplay::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Eventdisplay(void *p) {
      return  p ? new(p) ::Eventdisplay : new ::Eventdisplay;
   }
   static void *newArray_Eventdisplay(Long_t nElements, void *p) {
      return p ? new(p) ::Eventdisplay[nElements] : new ::Eventdisplay[nElements];
   }
   // Wrapper around operator delete
   static void delete_Eventdisplay(void *p) {
      delete ((::Eventdisplay*)p);
   }
   static void deleteArray_Eventdisplay(void *p) {
      delete [] ((::Eventdisplay*)p);
   }
   static void destruct_Eventdisplay(void *p) {
      typedef ::Eventdisplay current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Eventdisplay

//______________________________________________________________________________
void goodness_data::Streamer(TBuffer &R__b)
{
   // Stream an object of class goodness_data.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(goodness_data::Class(),this);
   } else {
      R__b.WriteClassBuffer(goodness_data::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_goodness_data(void *p) {
      return  p ? new(p) ::goodness_data : new ::goodness_data;
   }
   static void *newArray_goodness_data(Long_t nElements, void *p) {
      return p ? new(p) ::goodness_data[nElements] : new ::goodness_data[nElements];
   }
   // Wrapper around operator delete
   static void delete_goodness_data(void *p) {
      delete ((::goodness_data*)p);
   }
   static void deleteArray_goodness_data(void *p) {
      delete [] ((::goodness_data*)p);
   }
   static void destruct_goodness_data(void *p) {
      typedef ::goodness_data current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::goodness_data

//______________________________________________________________________________
void l_dir_data::Streamer(TBuffer &R__b)
{
   // Stream an object of class l_dir_data.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(l_dir_data::Class(),this);
   } else {
      R__b.WriteClassBuffer(l_dir_data::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_l_dir_data(void *p) {
      return  p ? new(p) ::l_dir_data : new ::l_dir_data;
   }
   static void *newArray_l_dir_data(Long_t nElements, void *p) {
      return p ? new(p) ::l_dir_data[nElements] : new ::l_dir_data[nElements];
   }
   // Wrapper around operator delete
   static void delete_l_dir_data(void *p) {
      delete ((::l_dir_data*)p);
   }
   static void deleteArray_l_dir_data(void *p) {
      delete [] ((::l_dir_data*)p);
   }
   static void destruct_l_dir_data(void *p) {
      typedef ::l_dir_data current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::l_dir_data

//______________________________________________________________________________
void AnalizedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class AnalizedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AnalizedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(AnalizedData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AnalizedData(void *p) {
      return  p ? new(p) ::AnalizedData : new ::AnalizedData;
   }
   static void *newArray_AnalizedData(Long_t nElements, void *p) {
      return p ? new(p) ::AnalizedData[nElements] : new ::AnalizedData[nElements];
   }
   // Wrapper around operator delete
   static void delete_AnalizedData(void *p) {
      delete ((::AnalizedData*)p);
   }
   static void deleteArray_AnalizedData(void *p) {
      delete [] ((::AnalizedData*)p);
   }
   static void destruct_AnalizedData(void *p) {
      typedef ::AnalizedData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AnalizedData

//______________________________________________________________________________
void C4Number::Streamer(TBuffer &R__b)
{
   // Stream an object of class C4Number.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(C4Number::Class(),this);
   } else {
      R__b.WriteClassBuffer(C4Number::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_C4Number(void *p) {
      return  p ? new(p) ::C4Number : new ::C4Number;
   }
   static void *newArray_C4Number(Long_t nElements, void *p) {
      return p ? new(p) ::C4Number[nElements] : new ::C4Number[nElements];
   }
   // Wrapper around operator delete
   static void delete_C4Number(void *p) {
      delete ((::C4Number*)p);
   }
   static void deleteArray_C4Number(void *p) {
      delete [] ((::C4Number*)p);
   }
   static void destruct_C4Number(void *p) {
      typedef ::C4Number current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::C4Number

//______________________________________________________________________________
void CSearch_range::Streamer(TBuffer &R__b)
{
   // Stream an object of class CSearch_range.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CSearch_range::Class(),this);
   } else {
      R__b.WriteClassBuffer(CSearch_range::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CSearch_range(void *p) {
      return  p ? new(p) ::CSearch_range : new ::CSearch_range;
   }
   static void *newArray_CSearch_range(Long_t nElements, void *p) {
      return p ? new(p) ::CSearch_range[nElements] : new ::CSearch_range[nElements];
   }
   // Wrapper around operator delete
   static void delete_CSearch_range(void *p) {
      delete ((::CSearch_range*)p);
   }
   static void deleteArray_CSearch_range(void *p) {
      delete [] ((::CSearch_range*)p);
   }
   static void destruct_CSearch_range(void *p) {
      typedef ::CSearch_range current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CSearch_range

//______________________________________________________________________________
void FileList::Streamer(TBuffer &R__b)
{
   // Stream an object of class FileList.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FileList::Class(),this);
   } else {
      R__b.WriteClassBuffer(FileList::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FileList(void *p) {
      return  p ? new(p) ::FileList : new ::FileList;
   }
   static void *newArray_FileList(Long_t nElements, void *p) {
      return p ? new(p) ::FileList[nElements] : new ::FileList[nElements];
   }
   // Wrapper around operator delete
   static void delete_FileList(void *p) {
      delete ((::FileList*)p);
   }
   static void deleteArray_FileList(void *p) {
      delete [] ((::FileList*)p);
   }
   static void destruct_FileList(void *p) {
      typedef ::FileList current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_FileList(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::FileList*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::FileList

//______________________________________________________________________________
void efficiency::Streamer(TBuffer &R__b)
{
   // Stream an object of class efficiency.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(efficiency::Class(),this);
   } else {
      R__b.WriteClassBuffer(efficiency::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_efficiency(void *p) {
      return  p ? new(p) ::efficiency : new ::efficiency;
   }
   static void *newArray_efficiency(Long_t nElements, void *p) {
      return p ? new(p) ::efficiency[nElements] : new ::efficiency[nElements];
   }
   // Wrapper around operator delete
   static void delete_efficiency(void *p) {
      delete ((::efficiency*)p);
   }
   static void deleteArray_efficiency(void *p) {
      delete [] ((::efficiency*)p);
   }
   static void destruct_efficiency(void *p) {
      typedef ::efficiency current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_efficiency(void *p, TDirectory *dir) {
      ((::efficiency*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t  merge_efficiency(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::efficiency*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::efficiency

//______________________________________________________________________________
void TH1DByTree::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH1DByTree.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH1DByTree::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH1DByTree::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH1DByTree(void *p) {
      return  p ? new(p) ::TH1DByTree : new ::TH1DByTree;
   }
   static void *newArray_TH1DByTree(Long_t nElements, void *p) {
      return p ? new(p) ::TH1DByTree[nElements] : new ::TH1DByTree[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH1DByTree(void *p) {
      delete ((::TH1DByTree*)p);
   }
   static void deleteArray_TH1DByTree(void *p) {
      delete [] ((::TH1DByTree*)p);
   }
   static void destruct_TH1DByTree(void *p) {
      typedef ::TH1DByTree current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_TH1DByTree(void *p, TDirectory *dir) {
      ((::TH1DByTree*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH1DByTree(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH1DByTree*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH1DByTree

//______________________________________________________________________________
void HistError::Streamer(TBuffer &R__b)
{
   // Stream an object of class HistError.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HistError::Class(),this);
   } else {
      R__b.WriteClassBuffer(HistError::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HistError(void *p) {
      return  p ? new(p) ::HistError : new ::HistError;
   }
   static void *newArray_HistError(Long_t nElements, void *p) {
      return p ? new(p) ::HistError[nElements] : new ::HistError[nElements];
   }
   // Wrapper around operator delete
   static void delete_HistError(void *p) {
      delete ((::HistError*)p);
   }
   static void deleteArray_HistError(void *p) {
      delete [] ((::HistError*)p);
   }
   static void destruct_HistError(void *p) {
      typedef ::HistError current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_HistError(void *p, TDirectory *dir) {
      ((::HistError*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t  merge_HistError(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::HistError*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::HistError

//______________________________________________________________________________
void HistBias::Streamer(TBuffer &R__b)
{
   // Stream an object of class HistBias.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HistBias::Class(),this);
   } else {
      R__b.WriteClassBuffer(HistBias::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HistBias(void *p) {
      return  p ? new(p) ::HistBias : new ::HistBias;
   }
   static void *newArray_HistBias(Long_t nElements, void *p) {
      return p ? new(p) ::HistBias[nElements] : new ::HistBias[nElements];
   }
   // Wrapper around operator delete
   static void delete_HistBias(void *p) {
      delete ((::HistBias*)p);
   }
   static void deleteArray_HistBias(void *p) {
      delete [] ((::HistBias*)p);
   }
   static void destruct_HistBias(void *p) {
      typedef ::HistBias current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_HistBias(void *p, TDirectory *dir) {
      ((::HistBias*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t  merge_HistBias(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::HistBias*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::HistBias

//______________________________________________________________________________
void AngleRange::Streamer(TBuffer &R__b)
{
   // Stream an object of class AngleRange.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AngleRange::Class(),this);
   } else {
      R__b.WriteClassBuffer(AngleRange::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AngleRange(void *p) {
      return  p ? new(p) ::AngleRange : new ::AngleRange;
   }
   static void *newArray_AngleRange(Long_t nElements, void *p) {
      return p ? new(p) ::AngleRange[nElements] : new ::AngleRange[nElements];
   }
   // Wrapper around operator delete
   static void delete_AngleRange(void *p) {
      delete ((::AngleRange*)p);
   }
   static void deleteArray_AngleRange(void *p) {
      delete [] ((::AngleRange*)p);
   }
   static void destruct_AngleRange(void *p) {
      typedef ::AngleRange current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AngleRange

//______________________________________________________________________________
void Thitinfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class Thitinfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Thitinfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(Thitinfo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Thitinfo(void *p) {
      return  p ? new(p) ::Thitinfo : new ::Thitinfo;
   }
   static void *newArray_Thitinfo(Long_t nElements, void *p) {
      return p ? new(p) ::Thitinfo[nElements] : new ::Thitinfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_Thitinfo(void *p) {
      delete ((::Thitinfo*)p);
   }
   static void deleteArray_Thitinfo(void *p) {
      delete [] ((::Thitinfo*)p);
   }
   static void destruct_Thitinfo(void *p) {
      typedef ::Thitinfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Thitinfo

//______________________________________________________________________________
void TReconstructdata::Streamer(TBuffer &R__b)
{
   // Stream an object of class TReconstructdata.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TReconstructdata::Class(),this);
   } else {
      R__b.WriteClassBuffer(TReconstructdata::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TReconstructdata(void *p) {
      return  p ? new(p) ::TReconstructdata : new ::TReconstructdata;
   }
   static void *newArray_TReconstructdata(Long_t nElements, void *p) {
      return p ? new(p) ::TReconstructdata[nElements] : new ::TReconstructdata[nElements];
   }
   // Wrapper around operator delete
   static void delete_TReconstructdata(void *p) {
      delete ((::TReconstructdata*)p);
   }
   static void deleteArray_TReconstructdata(void *p) {
      delete [] ((::TReconstructdata*)p);
   }
   static void destruct_TReconstructdata(void *p) {
      typedef ::TReconstructdata current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TReconstructdata

//______________________________________________________________________________
void TReconstructdata_minimize::Streamer(TBuffer &R__b)
{
   // Stream an object of class TReconstructdata_minimize.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TReconstructdata_minimize::Class(),this);
   } else {
      R__b.WriteClassBuffer(TReconstructdata_minimize::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TReconstructdata_minimize(void *p) {
      return  p ? new(p) ::TReconstructdata_minimize : new ::TReconstructdata_minimize;
   }
   static void *newArray_TReconstructdata_minimize(Long_t nElements, void *p) {
      return p ? new(p) ::TReconstructdata_minimize[nElements] : new ::TReconstructdata_minimize[nElements];
   }
   // Wrapper around operator delete
   static void delete_TReconstructdata_minimize(void *p) {
      delete ((::TReconstructdata_minimize*)p);
   }
   static void deleteArray_TReconstructdata_minimize(void *p) {
      delete [] ((::TReconstructdata_minimize*)p);
   }
   static void destruct_TReconstructdata_minimize(void *p) {
      typedef ::TReconstructdata_minimize current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TReconstructdata_minimize

//______________________________________________________________________________
void TReconstructhit::Streamer(TBuffer &R__b)
{
   // Stream an object of class TReconstructhit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TReconstructhit::Class(),this);
   } else {
      R__b.WriteClassBuffer(TReconstructhit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TReconstructhit(void *p) {
      return  p ? new(p) ::TReconstructhit : new ::TReconstructhit;
   }
   static void *newArray_TReconstructhit(Long_t nElements, void *p) {
      return p ? new(p) ::TReconstructhit[nElements] : new ::TReconstructhit[nElements];
   }
   // Wrapper around operator delete
   static void delete_TReconstructhit(void *p) {
      delete ((::TReconstructhit*)p);
   }
   static void deleteArray_TReconstructhit(void *p) {
      delete [] ((::TReconstructhit*)p);
   }
   static void destruct_TReconstructhit(void *p) {
      typedef ::TReconstructhit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TReconstructhit

//______________________________________________________________________________
void Tfunction::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfunction.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfunction::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfunction::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Tfunction(void *p) {
      delete ((::Tfunction*)p);
   }
   static void deleteArray_Tfunction(void *p) {
      delete [] ((::Tfunction*)p);
   }
   static void destruct_Tfunction(void *p) {
      typedef ::Tfunction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfunction

//______________________________________________________________________________
void Tafunction::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tafunction.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tafunction::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tafunction::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Tafunction(void *p) {
      delete ((::Tafunction*)p);
   }
   static void deleteArray_Tafunction(void *p) {
      delete [] ((::Tafunction*)p);
   }
   static void destruct_Tafunction(void *p) {
      typedef ::Tafunction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tafunction

//______________________________________________________________________________
void Tafuncprototype::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tafuncprototype.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tafuncprototype::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tafuncprototype::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tafuncprototype(void *p) {
      return  p ? new(p) ::Tafuncprototype : new ::Tafuncprototype;
   }
   static void *newArray_Tafuncprototype(Long_t nElements, void *p) {
      return p ? new(p) ::Tafuncprototype[nElements] : new ::Tafuncprototype[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tafuncprototype(void *p) {
      delete ((::Tafuncprototype*)p);
   }
   static void deleteArray_Tafuncprototype(void *p) {
      delete [] ((::Tafuncprototype*)p);
   }
   static void destruct_Tafuncprototype(void *p) {
      typedef ::Tafuncprototype current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tafuncprototype

//______________________________________________________________________________
void Tdistance_function::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tdistance_function.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tdistance_function::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tdistance_function::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Tdistance_function(void *p) {
      delete ((::Tdistance_function*)p);
   }
   static void deleteArray_Tdistance_function(void *p) {
      delete [] ((::Tdistance_function*)p);
   }
   static void destruct_Tdistance_function(void *p) {
      typedef ::Tdistance_function current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tdistance_function

//______________________________________________________________________________
void Tdistance_position_pmt::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tdistance_position_pmt.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tdistance_position_pmt::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tdistance_position_pmt::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tdistance_position_pmt(void *p) {
      return  p ? new(p) ::Tdistance_position_pmt : new ::Tdistance_position_pmt;
   }
   static void *newArray_Tdistance_position_pmt(Long_t nElements, void *p) {
      return p ? new(p) ::Tdistance_position_pmt[nElements] : new ::Tdistance_position_pmt[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tdistance_position_pmt(void *p) {
      delete ((::Tdistance_position_pmt*)p);
   }
   static void deleteArray_Tdistance_position_pmt(void *p) {
      delete [] ((::Tdistance_position_pmt*)p);
   }
   static void destruct_Tdistance_position_pmt(void *p) {
      typedef ::Tdistance_position_pmt current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tdistance_position_pmt

//______________________________________________________________________________
void Tdistance_position_retro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tdistance_position_retro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tdistance_position_retro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tdistance_position_retro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tdistance_position_retro(void *p) {
      return  p ? new(p) ::Tdistance_position_retro : new ::Tdistance_position_retro;
   }
   static void *newArray_Tdistance_position_retro(Long_t nElements, void *p) {
      return p ? new(p) ::Tdistance_position_retro[nElements] : new ::Tdistance_position_retro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tdistance_position_retro(void *p) {
      delete ((::Tdistance_position_retro*)p);
   }
   static void deleteArray_Tdistance_position_retro(void *p) {
      delete [] ((::Tdistance_position_retro*)p);
   }
   static void destruct_Tdistance_position_retro(void *p) {
      typedef ::Tdistance_position_retro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tdistance_position_retro

//______________________________________________________________________________
void Tdistance_fly_retro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tdistance_fly_retro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tdistance_fly_retro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tdistance_fly_retro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tdistance_fly_retro(void *p) {
      return  p ? new(p) ::Tdistance_fly_retro : new ::Tdistance_fly_retro;
   }
   static void *newArray_Tdistance_fly_retro(Long_t nElements, void *p) {
      return p ? new(p) ::Tdistance_fly_retro[nElements] : new ::Tdistance_fly_retro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tdistance_fly_retro(void *p) {
      delete ((::Tdistance_fly_retro*)p);
   }
   static void deleteArray_Tdistance_fly_retro(void *p) {
      delete [] ((::Tdistance_fly_retro*)p);
   }
   static void destruct_Tdistance_fly_retro(void *p) {
      typedef ::Tdistance_fly_retro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tdistance_fly_retro

//______________________________________________________________________________
void Tfdirection::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfdirection.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfdirection::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfdirection::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Tfdirection(void *p) {
      delete ((::Tfdirection*)p);
   }
   static void deleteArray_Tfdirection(void *p) {
      delete [] ((::Tfdirection*)p);
   }
   static void destruct_Tfdirection(void *p) {
      typedef ::Tfdirection current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfdirection

//______________________________________________________________________________
void Tfdirprototypenoretro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfdirprototypenoretro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfdirprototypenoretro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfdirprototypenoretro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfdirprototypenoretro(void *p) {
      return  p ? new(p) ::Tfdirprototypenoretro : new ::Tfdirprototypenoretro;
   }
   static void *newArray_Tfdirprototypenoretro(Long_t nElements, void *p) {
      return p ? new(p) ::Tfdirprototypenoretro[nElements] : new ::Tfdirprototypenoretro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfdirprototypenoretro(void *p) {
      delete ((::Tfdirprototypenoretro*)p);
   }
   static void deleteArray_Tfdirprototypenoretro(void *p) {
      delete [] ((::Tfdirprototypenoretro*)p);
   }
   static void destruct_Tfdirprototypenoretro(void *p) {
      typedef ::Tfdirprototypenoretro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfdirprototypenoretro

//______________________________________________________________________________
void Tfdirprototypeonretro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfdirprototypeonretro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfdirprototypeonretro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfdirprototypeonretro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfdirprototypeonretro(void *p) {
      return  p ? new(p) ::Tfdirprototypeonretro : new ::Tfdirprototypeonretro;
   }
   static void *newArray_Tfdirprototypeonretro(Long_t nElements, void *p) {
      return p ? new(p) ::Tfdirprototypeonretro[nElements] : new ::Tfdirprototypeonretro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfdirprototypeonretro(void *p) {
      delete ((::Tfdirprototypeonretro*)p);
   }
   static void deleteArray_Tfdirprototypeonretro(void *p) {
      delete [] ((::Tfdirprototypeonretro*)p);
   }
   static void destruct_Tfdirprototypeonretro(void *p) {
      typedef ::Tfdirprototypeonretro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfdirprototypeonretro

//______________________________________________________________________________
void Tfdirbydatanoretro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfdirbydatanoretro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfdirbydatanoretro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfdirbydatanoretro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfdirbydatanoretro(void *p) {
      return  p ? new(p) ::Tfdirbydatanoretro : new ::Tfdirbydatanoretro;
   }
   static void *newArray_Tfdirbydatanoretro(Long_t nElements, void *p) {
      return p ? new(p) ::Tfdirbydatanoretro[nElements] : new ::Tfdirbydatanoretro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfdirbydatanoretro(void *p) {
      delete ((::Tfdirbydatanoretro*)p);
   }
   static void deleteArray_Tfdirbydatanoretro(void *p) {
      delete [] ((::Tfdirbydatanoretro*)p);
   }
   static void destruct_Tfdirbydatanoretro(void *p) {
      typedef ::Tfdirbydatanoretro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfdirbydatanoretro

//______________________________________________________________________________
void Tfdirbydataonretro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfdirbydataonretro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfdirbydataonretro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfdirbydataonretro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfdirbydataonretro(void *p) {
      return  p ? new(p) ::Tfdirbydataonretro : new ::Tfdirbydataonretro;
   }
   static void *newArray_Tfdirbydataonretro(Long_t nElements, void *p) {
      return p ? new(p) ::Tfdirbydataonretro[nElements] : new ::Tfdirbydataonretro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfdirbydataonretro(void *p) {
      delete ((::Tfdirbydataonretro*)p);
   }
   static void deleteArray_Tfdirbydataonretro(void *p) {
      delete [] ((::Tfdirbydataonretro*)p);
   }
   static void destruct_Tfdirbydataonretro(void *p) {
      typedef ::Tfdirbydataonretro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfdirbydataonretro

//______________________________________________________________________________
void Tlikelihood::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tlikelihood.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tlikelihood::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tlikelihood::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Tlikelihood(void *p) {
      delete ((::Tlikelihood*)p);
   }
   static void deleteArray_Tlikelihood(void *p) {
      delete [] ((::Tlikelihood*)p);
   }
   static void destruct_Tlikelihood(void *p) {
      typedef ::Tlikelihood current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tlikelihood

//______________________________________________________________________________
void Tlikelihoodnoretro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tlikelihoodnoretro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tlikelihoodnoretro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tlikelihoodnoretro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tlikelihoodnoretro(void *p) {
      return  p ? new(p) ::Tlikelihoodnoretro : new ::Tlikelihoodnoretro;
   }
   static void *newArray_Tlikelihoodnoretro(Long_t nElements, void *p) {
      return p ? new(p) ::Tlikelihoodnoretro[nElements] : new ::Tlikelihoodnoretro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tlikelihoodnoretro(void *p) {
      delete ((::Tlikelihoodnoretro*)p);
   }
   static void deleteArray_Tlikelihoodnoretro(void *p) {
      delete [] ((::Tlikelihoodnoretro*)p);
   }
   static void destruct_Tlikelihoodnoretro(void *p) {
      typedef ::Tlikelihoodnoretro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tlikelihoodnoretro

//______________________________________________________________________________
void Tlikelihoodonretro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tlikelihoodonretro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tlikelihoodonretro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tlikelihoodonretro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tlikelihoodonretro(void *p) {
      return  p ? new(p) ::Tlikelihoodonretro : new ::Tlikelihoodonretro;
   }
   static void *newArray_Tlikelihoodonretro(Long_t nElements, void *p) {
      return p ? new(p) ::Tlikelihoodonretro[nElements] : new ::Tlikelihoodonretro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tlikelihoodonretro(void *p) {
      delete ((::Tlikelihoodonretro*)p);
   }
   static void deleteArray_Tlikelihoodonretro(void *p) {
      delete [] ((::Tlikelihoodonretro*)p);
   }
   static void destruct_Tlikelihoodonretro(void *p) {
      typedef ::Tlikelihoodonretro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tlikelihoodonretro

//______________________________________________________________________________
void Tlikelihoodsum::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tlikelihoodsum.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tlikelihoodsum::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tlikelihoodsum::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tlikelihoodsum(void *p) {
      return  p ? new(p) ::Tlikelihoodsum : new ::Tlikelihoodsum;
   }
   static void *newArray_Tlikelihoodsum(Long_t nElements, void *p) {
      return p ? new(p) ::Tlikelihoodsum[nElements] : new ::Tlikelihoodsum[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tlikelihoodsum(void *p) {
      delete ((::Tlikelihoodsum*)p);
   }
   static void deleteArray_Tlikelihoodsum(void *p) {
      delete [] ((::Tlikelihoodsum*)p);
   }
   static void destruct_Tlikelihoodsum(void *p) {
      typedef ::Tlikelihoodsum current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tlikelihoodsum

//______________________________________________________________________________
void Ttheta_dir_i::Streamer(TBuffer &R__b)
{
   // Stream an object of class Ttheta_dir_i.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Ttheta_dir_i::Class(),this);
   } else {
      R__b.WriteClassBuffer(Ttheta_dir_i::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Ttheta_dir_i(void *p) {
      return  p ? new(p) ::Ttheta_dir_i : new ::Ttheta_dir_i;
   }
   static void *newArray_Ttheta_dir_i(Long_t nElements, void *p) {
      return p ? new(p) ::Ttheta_dir_i[nElements] : new ::Ttheta_dir_i[nElements];
   }
   // Wrapper around operator delete
   static void delete_Ttheta_dir_i(void *p) {
      delete ((::Ttheta_dir_i*)p);
   }
   static void deleteArray_Ttheta_dir_i(void *p) {
      delete [] ((::Ttheta_dir_i*)p);
   }
   static void destruct_Ttheta_dir_i(void *p) {
      typedef ::Ttheta_dir_i current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Ttheta_dir_i

//______________________________________________________________________________
void Ttheta_i_func::Streamer(TBuffer &R__b)
{
   // Stream an object of class Ttheta_i_func.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Ttheta_i_func::Class(),this);
   } else {
      R__b.WriteClassBuffer(Ttheta_i_func::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Ttheta_i_func(void *p) {
      return  p ? new(p) ::Ttheta_i_func : new ::Ttheta_i_func;
   }
   static void *newArray_Ttheta_i_func(Long_t nElements, void *p) {
      return p ? new(p) ::Ttheta_i_func[nElements] : new ::Ttheta_i_func[nElements];
   }
   // Wrapper around operator delete
   static void delete_Ttheta_i_func(void *p) {
      delete ((::Ttheta_i_func*)p);
   }
   static void deleteArray_Ttheta_i_func(void *p) {
      delete [] ((::Ttheta_i_func*)p);
   }
   static void destruct_Ttheta_i_func(void *p) {
      typedef ::Ttheta_i_func current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Ttheta_i_func

//______________________________________________________________________________
void Ttof::Streamer(TBuffer &R__b)
{
   // Stream an object of class Ttof.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Ttof::Class(),this);
   } else {
      R__b.WriteClassBuffer(Ttof::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Ttof(void *p) {
      return  p ? new(p) ::Ttof : new ::Ttof;
   }
   static void *newArray_Ttof(Long_t nElements, void *p) {
      return p ? new(p) ::Ttof[nElements] : new ::Ttof[nElements];
   }
   // Wrapper around operator delete
   static void delete_Ttof(void *p) {
      delete ((::Ttof*)p);
   }
   static void deleteArray_Ttof(void *p) {
      delete [] ((::Ttof*)p);
   }
   static void destruct_Ttof(void *p) {
      typedef ::Ttof current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Ttof

//______________________________________________________________________________
void Tfgoodnessdirection::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfgoodnessdirection.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfgoodnessdirection::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfgoodnessdirection::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfgoodnessdirection(void *p) {
      return  p ? new(p) ::Tfgoodnessdirection : new ::Tfgoodnessdirection;
   }
   static void *newArray_Tfgoodnessdirection(Long_t nElements, void *p) {
      return p ? new(p) ::Tfgoodnessdirection[nElements] : new ::Tfgoodnessdirection[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfgoodnessdirection(void *p) {
      delete ((::Tfgoodnessdirection*)p);
   }
   static void deleteArray_Tfgoodnessdirection(void *p) {
      delete [] ((::Tfgoodnessdirection*)p);
   }
   static void destruct_Tfgoodnessdirection(void *p) {
      typedef ::Tfgoodnessdirection current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfgoodnessdirection

//______________________________________________________________________________
void TOption_minimize::Streamer(TBuffer &R__b)
{
   // Stream an object of class TOption_minimize.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TOption_minimize::Class(),this);
   } else {
      R__b.WriteClassBuffer(TOption_minimize::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TOption_minimize(void *p) {
      return  p ? new(p) ::TOption_minimize : new ::TOption_minimize;
   }
   static void *newArray_TOption_minimize(Long_t nElements, void *p) {
      return p ? new(p) ::TOption_minimize[nElements] : new ::TOption_minimize[nElements];
   }
   // Wrapper around operator delete
   static void delete_TOption_minimize(void *p) {
      delete ((::TOption_minimize*)p);
   }
   static void deleteArray_TOption_minimize(void *p) {
      delete [] ((::TOption_minimize*)p);
   }
   static void destruct_TOption_minimize(void *p) {
      typedef ::TOption_minimize current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TOption_minimize

//______________________________________________________________________________
void Tfgoodness::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfgoodness.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfgoodness::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfgoodness::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfgoodness(void *p) {
      return  p ? new(p) ::Tfgoodness : new ::Tfgoodness;
   }
   static void *newArray_Tfgoodness(Long_t nElements, void *p) {
      return p ? new(p) ::Tfgoodness[nElements] : new ::Tfgoodness[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfgoodness(void *p) {
      delete ((::Tfgoodness*)p);
   }
   static void deleteArray_Tfgoodness(void *p) {
      delete [] ((::Tfgoodness*)p);
   }
   static void destruct_Tfgoodness(void *p) {
      typedef ::Tfgoodness current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfgoodness

//______________________________________________________________________________
void Tfsumgoodness::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfsumgoodness.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfsumgoodness::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfsumgoodness::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Tfsumgoodness(void *p) {
      delete ((::Tfsumgoodness*)p);
   }
   static void deleteArray_Tfsumgoodness(void *p) {
      delete [] ((::Tfsumgoodness*)p);
   }
   static void destruct_Tfsumgoodness(void *p) {
      typedef ::Tfsumgoodness current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfsumgoodness

//______________________________________________________________________________
void Tfsumgoodnessnoretro::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfsumgoodnessnoretro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfsumgoodnessnoretro::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfsumgoodnessnoretro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfsumgoodnessnoretro(void *p) {
      return  p ? new(p) ::Tfsumgoodnessnoretro : new ::Tfsumgoodnessnoretro;
   }
   static void *newArray_Tfsumgoodnessnoretro(Long_t nElements, void *p) {
      return p ? new(p) ::Tfsumgoodnessnoretro[nElements] : new ::Tfsumgoodnessnoretro[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfsumgoodnessnoretro(void *p) {
      delete ((::Tfsumgoodnessnoretro*)p);
   }
   static void deleteArray_Tfsumgoodnessnoretro(void *p) {
      delete [] ((::Tfsumgoodnessnoretro*)p);
   }
   static void destruct_Tfsumgoodnessnoretro(void *p) {
      typedef ::Tfsumgoodnessnoretro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfsumgoodnessnoretro

//______________________________________________________________________________
void Tfsumgoodnesssum::Streamer(TBuffer &R__b)
{
   // Stream an object of class Tfsumgoodnesssum.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Tfsumgoodnesssum::Class(),this);
   } else {
      R__b.WriteClassBuffer(Tfsumgoodnesssum::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Tfsumgoodnesssum(void *p) {
      return  p ? new(p) ::Tfsumgoodnesssum : new ::Tfsumgoodnesssum;
   }
   static void *newArray_Tfsumgoodnesssum(Long_t nElements, void *p) {
      return p ? new(p) ::Tfsumgoodnesssum[nElements] : new ::Tfsumgoodnesssum[nElements];
   }
   // Wrapper around operator delete
   static void delete_Tfsumgoodnesssum(void *p) {
      delete ((::Tfsumgoodnesssum*)p);
   }
   static void deleteArray_Tfsumgoodnesssum(void *p) {
      delete [] ((::Tfsumgoodnesssum*)p);
   }
   static void destruct_Tfsumgoodnesssum(void *p) {
      typedef ::Tfsumgoodnesssum current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Tfsumgoodnesssum

//______________________________________________________________________________
void BiasError::Streamer(TBuffer &R__b)
{
   // Stream an object of class BiasError.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(BiasError::Class(),this);
   } else {
      R__b.WriteClassBuffer(BiasError::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BiasError(void *p) {
      return  p ? new(p) ::BiasError : new ::BiasError;
   }
   static void *newArray_BiasError(Long_t nElements, void *p) {
      return p ? new(p) ::BiasError[nElements] : new ::BiasError[nElements];
   }
   // Wrapper around operator delete
   static void delete_BiasError(void *p) {
      delete ((::BiasError*)p);
   }
   static void deleteArray_BiasError(void *p) {
      delete [] ((::BiasError*)p);
   }
   static void destruct_BiasError(void *p) {
      typedef ::BiasError current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BiasError

//______________________________________________________________________________
void AnalizeTag::Streamer(TBuffer &R__b)
{
   // Stream an object of class AnalizeTag.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AnalizeTag::Class(),this);
   } else {
      R__b.WriteClassBuffer(AnalizeTag::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AnalizeTag(void *p) {
      return  p ? new(p) ::AnalizeTag : new ::AnalizeTag;
   }
   static void *newArray_AnalizeTag(Long_t nElements, void *p) {
      return p ? new(p) ::AnalizeTag[nElements] : new ::AnalizeTag[nElements];
   }
   // Wrapper around operator delete
   static void delete_AnalizeTag(void *p) {
      delete ((::AnalizeTag*)p);
   }
   static void deleteArray_AnalizeTag(void *p) {
      delete [] ((::AnalizeTag*)p);
   }
   static void destruct_AnalizeTag(void *p) {
      typedef ::AnalizeTag current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AnalizeTag

//______________________________________________________________________________
void AnalizeFile::Streamer(TBuffer &R__b)
{
   // Stream an object of class AnalizeFile.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AnalizeFile::Class(),this);
   } else {
      R__b.WriteClassBuffer(AnalizeFile::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AnalizeFile(void *p) {
      return  p ? new(p) ::AnalizeFile : new ::AnalizeFile;
   }
   static void *newArray_AnalizeFile(Long_t nElements, void *p) {
      return p ? new(p) ::AnalizeFile[nElements] : new ::AnalizeFile[nElements];
   }
   // Wrapper around operator delete
   static void delete_AnalizeFile(void *p) {
      delete ((::AnalizeFile*)p);
   }
   static void deleteArray_AnalizeFile(void *p) {
      delete [] ((::AnalizeFile*)p);
   }
   static void destruct_AnalizeFile(void *p) {
      typedef ::AnalizeFile current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AnalizeFile

//______________________________________________________________________________
void FileManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FileManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FileManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FileManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FileManager(void *p) {
      return  p ? new(p) ::FileManager : new ::FileManager;
   }
   static void *newArray_FileManager(Long_t nElements, void *p) {
      return p ? new(p) ::FileManager[nElements] : new ::FileManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_FileManager(void *p) {
      delete ((::FileManager*)p);
   }
   static void deleteArray_FileManager(void *p) {
      delete [] ((::FileManager*)p);
   }
   static void destruct_FileManager(void *p) {
      typedef ::FileManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FileManager

//______________________________________________________________________________
void AnalizeManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class AnalizeManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AnalizeManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(AnalizeManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AnalizeManager(void *p) {
      return  p ? new(p) ::AnalizeManager : new ::AnalizeManager;
   }
   static void *newArray_AnalizeManager(Long_t nElements, void *p) {
      return p ? new(p) ::AnalizeManager[nElements] : new ::AnalizeManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_AnalizeManager(void *p) {
      delete ((::AnalizeManager*)p);
   }
   static void deleteArray_AnalizeManager(void *p) {
      delete [] ((::AnalizeManager*)p);
   }
   static void destruct_AnalizeManager(void *p) {
      typedef ::AnalizeManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AnalizeManager

//______________________________________________________________________________
void TNinWater::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNinWater.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNinWater::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNinWater::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNinWater(void *p) {
      return  p ? new(p) ::TNinWater : new ::TNinWater;
   }
   static void *newArray_TNinWater(Long_t nElements, void *p) {
      return p ? new(p) ::TNinWater[nElements] : new ::TNinWater[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNinWater(void *p) {
      delete ((::TNinWater*)p);
   }
   static void deleteArray_TNinWater(void *p) {
      delete [] ((::TNinWater*)p);
   }
   static void destruct_TNinWater(void *p) {
      typedef ::TNinWater current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TNinWater

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 339,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 339,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEThitinfogR_Dictionary();
   static void vectorlEThitinfogR_TClassManip(TClass*);
   static void *new_vectorlEThitinfogR(void *p = 0);
   static void *newArray_vectorlEThitinfogR(Long_t size, void *p);
   static void delete_vectorlEThitinfogR(void *p);
   static void deleteArray_vectorlEThitinfogR(void *p);
   static void destruct_vectorlEThitinfogR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Thitinfo>*)
   {
      vector<Thitinfo> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Thitinfo>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Thitinfo>", -2, "vector", 339,
                  typeid(vector<Thitinfo>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEThitinfogR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Thitinfo>) );
      instance.SetNew(&new_vectorlEThitinfogR);
      instance.SetNewArray(&newArray_vectorlEThitinfogR);
      instance.SetDelete(&delete_vectorlEThitinfogR);
      instance.SetDeleteArray(&deleteArray_vectorlEThitinfogR);
      instance.SetDestructor(&destruct_vectorlEThitinfogR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Thitinfo> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Thitinfo>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEThitinfogR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Thitinfo>*)0x0)->GetClass();
      vectorlEThitinfogR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEThitinfogR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEThitinfogR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Thitinfo> : new vector<Thitinfo>;
   }
   static void *newArray_vectorlEThitinfogR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Thitinfo>[nElements] : new vector<Thitinfo>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEThitinfogR(void *p) {
      delete ((vector<Thitinfo>*)p);
   }
   static void deleteArray_vectorlEThitinfogR(void *p) {
      delete [] ((vector<Thitinfo>*)p);
   }
   static void destruct_vectorlEThitinfogR(void *p) {
      typedef vector<Thitinfo> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Thitinfo>

namespace ROOT {
   static TClass *vectorlETReconstructhitgR_Dictionary();
   static void vectorlETReconstructhitgR_TClassManip(TClass*);
   static void *new_vectorlETReconstructhitgR(void *p = 0);
   static void *newArray_vectorlETReconstructhitgR(Long_t size, void *p);
   static void delete_vectorlETReconstructhitgR(void *p);
   static void deleteArray_vectorlETReconstructhitgR(void *p);
   static void destruct_vectorlETReconstructhitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TReconstructhit>*)
   {
      vector<TReconstructhit> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TReconstructhit>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TReconstructhit>", -2, "vector", 339,
                  typeid(vector<TReconstructhit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETReconstructhitgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TReconstructhit>) );
      instance.SetNew(&new_vectorlETReconstructhitgR);
      instance.SetNewArray(&newArray_vectorlETReconstructhitgR);
      instance.SetDelete(&delete_vectorlETReconstructhitgR);
      instance.SetDeleteArray(&deleteArray_vectorlETReconstructhitgR);
      instance.SetDestructor(&destruct_vectorlETReconstructhitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TReconstructhit> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TReconstructhit>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETReconstructhitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TReconstructhit>*)0x0)->GetClass();
      vectorlETReconstructhitgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETReconstructhitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETReconstructhitgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TReconstructhit> : new vector<TReconstructhit>;
   }
   static void *newArray_vectorlETReconstructhitgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TReconstructhit>[nElements] : new vector<TReconstructhit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETReconstructhitgR(void *p) {
      delete ((vector<TReconstructhit>*)p);
   }
   static void deleteArray_vectorlETReconstructhitgR(void *p) {
      delete [] ((vector<TReconstructhit>*)p);
   }
   static void destruct_vectorlETReconstructhitgR(void *p) {
      typedef vector<TReconstructhit> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TReconstructhit>

namespace ROOT {
   static TClass *vectorlEAnalizeTaggR_Dictionary();
   static void vectorlEAnalizeTaggR_TClassManip(TClass*);
   static void *new_vectorlEAnalizeTaggR(void *p = 0);
   static void *newArray_vectorlEAnalizeTaggR(Long_t size, void *p);
   static void delete_vectorlEAnalizeTaggR(void *p);
   static void deleteArray_vectorlEAnalizeTaggR(void *p);
   static void destruct_vectorlEAnalizeTaggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AnalizeTag>*)
   {
      vector<AnalizeTag> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AnalizeTag>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AnalizeTag>", -2, "vector", 339,
                  typeid(vector<AnalizeTag>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAnalizeTaggR_Dictionary, isa_proxy, 4,
                  sizeof(vector<AnalizeTag>) );
      instance.SetNew(&new_vectorlEAnalizeTaggR);
      instance.SetNewArray(&newArray_vectorlEAnalizeTaggR);
      instance.SetDelete(&delete_vectorlEAnalizeTaggR);
      instance.SetDeleteArray(&deleteArray_vectorlEAnalizeTaggR);
      instance.SetDestructor(&destruct_vectorlEAnalizeTaggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AnalizeTag> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<AnalizeTag>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAnalizeTaggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AnalizeTag>*)0x0)->GetClass();
      vectorlEAnalizeTaggR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAnalizeTaggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAnalizeTaggR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AnalizeTag> : new vector<AnalizeTag>;
   }
   static void *newArray_vectorlEAnalizeTaggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AnalizeTag>[nElements] : new vector<AnalizeTag>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAnalizeTaggR(void *p) {
      delete ((vector<AnalizeTag>*)p);
   }
   static void deleteArray_vectorlEAnalizeTaggR(void *p) {
      delete [] ((vector<AnalizeTag>*)p);
   }
   static void destruct_vectorlEAnalizeTaggR(void *p) {
      typedef vector<AnalizeTag> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AnalizeTag>

namespace ROOT {
   static TClass *vectorlEAnalizeFilegR_Dictionary();
   static void vectorlEAnalizeFilegR_TClassManip(TClass*);
   static void *new_vectorlEAnalizeFilegR(void *p = 0);
   static void *newArray_vectorlEAnalizeFilegR(Long_t size, void *p);
   static void delete_vectorlEAnalizeFilegR(void *p);
   static void deleteArray_vectorlEAnalizeFilegR(void *p);
   static void destruct_vectorlEAnalizeFilegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AnalizeFile>*)
   {
      vector<AnalizeFile> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AnalizeFile>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AnalizeFile>", -2, "vector", 339,
                  typeid(vector<AnalizeFile>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAnalizeFilegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<AnalizeFile>) );
      instance.SetNew(&new_vectorlEAnalizeFilegR);
      instance.SetNewArray(&newArray_vectorlEAnalizeFilegR);
      instance.SetDelete(&delete_vectorlEAnalizeFilegR);
      instance.SetDeleteArray(&deleteArray_vectorlEAnalizeFilegR);
      instance.SetDestructor(&destruct_vectorlEAnalizeFilegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AnalizeFile> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<AnalizeFile>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAnalizeFilegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AnalizeFile>*)0x0)->GetClass();
      vectorlEAnalizeFilegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAnalizeFilegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAnalizeFilegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AnalizeFile> : new vector<AnalizeFile>;
   }
   static void *newArray_vectorlEAnalizeFilegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AnalizeFile>[nElements] : new vector<AnalizeFile>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAnalizeFilegR(void *p) {
      delete ((vector<AnalizeFile>*)p);
   }
   static void deleteArray_vectorlEAnalizeFilegR(void *p) {
      delete [] ((vector<AnalizeFile>*)p);
   }
   static void destruct_vectorlEAnalizeFilegR(void *p) {
      typedef vector<AnalizeFile> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AnalizeFile>

namespace ROOT {
   static TClass *maplEstringcOmaplEstringcOAnalizeFilegRsPgR_Dictionary();
   static void maplEstringcOmaplEstringcOAnalizeFilegRsPgR_TClassManip(TClass*);
   static void *new_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p = 0);
   static void *newArray_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(Long_t size, void *p);
   static void delete_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p);
   static void deleteArray_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p);
   static void destruct_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,map<string,AnalizeFile> >*)
   {
      map<string,map<string,AnalizeFile> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,map<string,AnalizeFile> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,map<string,AnalizeFile> >", -2, "map", 100,
                  typeid(map<string,map<string,AnalizeFile> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOmaplEstringcOAnalizeFilegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,map<string,AnalizeFile> >) );
      instance.SetNew(&new_maplEstringcOmaplEstringcOAnalizeFilegRsPgR);
      instance.SetNewArray(&newArray_maplEstringcOmaplEstringcOAnalizeFilegRsPgR);
      instance.SetDelete(&delete_maplEstringcOmaplEstringcOAnalizeFilegRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOmaplEstringcOAnalizeFilegRsPgR);
      instance.SetDestructor(&destruct_maplEstringcOmaplEstringcOAnalizeFilegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,map<string,AnalizeFile> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,map<string,AnalizeFile> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOmaplEstringcOAnalizeFilegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,map<string,AnalizeFile> >*)0x0)->GetClass();
      maplEstringcOmaplEstringcOAnalizeFilegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOmaplEstringcOAnalizeFilegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,map<string,AnalizeFile> > : new map<string,map<string,AnalizeFile> >;
   }
   static void *newArray_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,map<string,AnalizeFile> >[nElements] : new map<string,map<string,AnalizeFile> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p) {
      delete ((map<string,map<string,AnalizeFile> >*)p);
   }
   static void deleteArray_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p) {
      delete [] ((map<string,map<string,AnalizeFile> >*)p);
   }
   static void destruct_maplEstringcOmaplEstringcOAnalizeFilegRsPgR(void *p) {
      typedef map<string,map<string,AnalizeFile> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,map<string,AnalizeFile> >

namespace ROOT {
   static TClass *maplEstringcOAnalizeFilegR_Dictionary();
   static void maplEstringcOAnalizeFilegR_TClassManip(TClass*);
   static void *new_maplEstringcOAnalizeFilegR(void *p = 0);
   static void *newArray_maplEstringcOAnalizeFilegR(Long_t size, void *p);
   static void delete_maplEstringcOAnalizeFilegR(void *p);
   static void deleteArray_maplEstringcOAnalizeFilegR(void *p);
   static void destruct_maplEstringcOAnalizeFilegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,AnalizeFile>*)
   {
      map<string,AnalizeFile> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,AnalizeFile>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,AnalizeFile>", -2, "map", 100,
                  typeid(map<string,AnalizeFile>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOAnalizeFilegR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,AnalizeFile>) );
      instance.SetNew(&new_maplEstringcOAnalizeFilegR);
      instance.SetNewArray(&newArray_maplEstringcOAnalizeFilegR);
      instance.SetDelete(&delete_maplEstringcOAnalizeFilegR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOAnalizeFilegR);
      instance.SetDestructor(&destruct_maplEstringcOAnalizeFilegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,AnalizeFile> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,AnalizeFile>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOAnalizeFilegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,AnalizeFile>*)0x0)->GetClass();
      maplEstringcOAnalizeFilegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOAnalizeFilegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOAnalizeFilegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,AnalizeFile> : new map<string,AnalizeFile>;
   }
   static void *newArray_maplEstringcOAnalizeFilegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,AnalizeFile>[nElements] : new map<string,AnalizeFile>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOAnalizeFilegR(void *p) {
      delete ((map<string,AnalizeFile>*)p);
   }
   static void deleteArray_maplEstringcOAnalizeFilegR(void *p) {
      delete [] ((map<string,AnalizeFile>*)p);
   }
   static void destruct_maplEstringcOAnalizeFilegR(void *p) {
      typedef map<string,AnalizeFile> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,AnalizeFile>

namespace {
  void TriggerDictionaryInitialization_libmacroRootDict_Impl() {
    static const char* headers[] = {
"/rhome/fujigami/retro/lowe/source/macro/include/eventdisplay.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/goodness_data.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/likelihood_direction_data.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/AnalizedData.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/CSearch_range.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/C4Number.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/FileList.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/efficiency.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/HistByTree.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/HistError.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/HistBias.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/AngleRange.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Thitinfo.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/TReconstructdata.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tfunction.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tafunction.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tdistance_function.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tlikelihood.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_dir_i.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_i_func.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Ttof.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodnessdirection.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/TOption_minimize.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodness.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/Tfsumgoodness.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/BiasError.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/FileManager.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/AnalizeTag.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/AnalizeManager.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/AnalizeFile.hh",
"/rhome/fujigami/retro/lowe/source/macro/include/TNinWater.hh",
0
    };
    static const char* includePaths[] = {
"/rhome/fujigami/retro/root-6.08.02_build/include",
"/rhome/fujigami/retro/WCSim/include",
"/rhome/fujigami/retro/geant4-10.4.1-customOpBoundary-install/include/Geant4",
"/rhome/fujigami/retro/root-6.08.02_build/include",
"/rhome/fujigami/retro/lowe/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libmacroRootDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/FileManager.hh")))  AnalizeTag;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/FileManager.hh")))  AnalizeFile;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/eventdisplay.hh")))  Eventdisplay;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/goodness_data.hh")))  goodness_data;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/likelihood_direction_data.hh")))  l_dir_data;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/AnalizedData.hh")))  AnalizedData;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/CSearch_range.hh")))  C4Number;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/CSearch_range.hh")))  CSearch_range;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/FileList.hh")))  FileList;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/efficiency.hh")))  efficiency;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/HistByTree.hh")))  TH1DByTree;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/HistError.hh")))  HistError;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/HistBias.hh")))  HistBias;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/AngleRange.hh")))  AngleRange;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Thitinfo.hh")))  Thitinfo;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/TReconstructdata.hh")))  TReconstructdata;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/TReconstructdata.hh")))  TReconstructdata_minimize;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/TReconstructdata.hh")))  TReconstructhit;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfunction.hh")))  Tfunction;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tafunction.hh")))  Tafunction;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tafunction.hh")))  Tafuncprototype;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tdistance_function.hh")))  Tdistance_function;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tdistance_function.hh")))  Tdistance_position_pmt;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tdistance_function.hh")))  Tdistance_position_retro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tdistance_function.hh")))  Tdistance_fly_retro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh")))  Tfdirection;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh")))  Tfdirprototypenoretro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh")))  Tfdirprototypeonretro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh")))  Tfdirbydatanoretro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh")))  Tfdirbydataonretro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tlikelihood.hh")))  Tlikelihood;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tlikelihood.hh")))  Tlikelihoodnoretro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tlikelihood.hh")))  Tlikelihoodonretro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tlikelihood.hh")))  Tlikelihoodsum;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_dir_i.hh")))  Ttheta_dir_i;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_i_func.hh")))  Ttheta_i_func;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Ttof.hh")))  Ttof;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodnessdirection.hh")))  Tfgoodnessdirection;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/TOption_minimize.hh")))  TOption_minimize;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodness.hh")))  Tfgoodness;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfsumgoodness.hh")))  Tfsumgoodness;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfsumgoodness.hh")))  Tfsumgoodnessnoretro;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/Tfsumgoodness.hh")))  Tfsumgoodnesssum;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/BiasError.hh")))  BiasError;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/FileManager.hh")))  FileManager;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/AnalizeManager.hh")))  AnalizeManager;
class __attribute__((annotate("$clingAutoload$/rhome/fujigami/retro/lowe/source/macro/include/TNinWater.hh")))  TNinWater;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libmacroRootDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/rhome/fujigami/retro/lowe/source/macro/include/eventdisplay.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/goodness_data.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/likelihood_direction_data.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizedData.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/CSearch_range.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/C4Number.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/FileList.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/efficiency.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/HistByTree.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/HistError.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/HistBias.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AngleRange.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Thitinfo.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/TReconstructdata.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfunction.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tafunction.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tdistance_function.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfdirection.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tlikelihood.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_dir_i.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Ttheta_i_func.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Ttof.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodnessdirection.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/TOption_minimize.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfgoodness.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/Tfsumgoodness.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/BiasError.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/FileManager.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizeTag.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizeManager.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/AnalizeFile.hh"
#include "/rhome/fujigami/retro/lowe/source/macro/include/TNinWater.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"AnalizeFile", payloadCode, "@",
"AnalizeManager", payloadCode, "@",
"AnalizeTag", payloadCode, "@",
"AnalizedData", payloadCode, "@",
"AngleRange", payloadCode, "@",
"BiasError", payloadCode, "@",
"C4Number", payloadCode, "@",
"CSearch_range", payloadCode, "@",
"Eventdisplay", payloadCode, "@",
"FileList", payloadCode, "@",
"FileManager", payloadCode, "@",
"HistBias", payloadCode, "@",
"HistError", payloadCode, "@",
"TH1DByTree", payloadCode, "@",
"TNinWater", payloadCode, "@",
"TOption_minimize", payloadCode, "@",
"TReconstructdata", payloadCode, "@",
"TReconstructdata_minimize", payloadCode, "@",
"TReconstructhit", payloadCode, "@",
"Tafuncprototype", payloadCode, "@",
"Tafunction", payloadCode, "@",
"Tdistance_fly_retro", payloadCode, "@",
"Tdistance_function", payloadCode, "@",
"Tdistance_position_pmt", payloadCode, "@",
"Tdistance_position_retro", payloadCode, "@",
"Tfdirbydatanoretro", payloadCode, "@",
"Tfdirbydataonretro", payloadCode, "@",
"Tfdirection", payloadCode, "@",
"Tfdirprototypenoretro", payloadCode, "@",
"Tfdirprototypeonretro", payloadCode, "@",
"Tfgoodness", payloadCode, "@",
"Tfgoodnessdirection", payloadCode, "@",
"Tfsumgoodness", payloadCode, "@",
"Tfsumgoodnessnoretro", payloadCode, "@",
"Tfsumgoodnesssum", payloadCode, "@",
"Tfunction", payloadCode, "@",
"Thitinfo", payloadCode, "@",
"Tlikelihood", payloadCode, "@",
"Tlikelihoodnoretro", payloadCode, "@",
"Tlikelihoodonretro", payloadCode, "@",
"Tlikelihoodsum", payloadCode, "@",
"Ttheta_dir_i", payloadCode, "@",
"Ttheta_i_func", payloadCode, "@",
"Ttof", payloadCode, "@",
"efficiency", payloadCode, "@",
"goodness_data", payloadCode, "@",
"l_dir_data", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libmacroRootDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libmacroRootDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libmacroRootDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libmacroRootDict() {
  TriggerDictionaryInitialization_libmacroRootDict_Impl();
}
