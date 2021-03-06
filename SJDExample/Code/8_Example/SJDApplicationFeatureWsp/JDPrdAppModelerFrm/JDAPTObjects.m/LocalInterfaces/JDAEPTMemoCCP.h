// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTMemoCCP.h
// Provide implementation to interface
//    CATICutAndPastable

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	JDAPTMemo
//EXTENSIONTYPE:	DataExtension

//    TIE: CATICutAndPastable

//End CAA2 Wizard Generation Report
//
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#ifndef JDAEPTMemoCCP_H
#define JDAEPTMemoCCP_H

#include "ObjectCCP_SPEC.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATICutAndPastable
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class JDAEPTMemoCCP: public ObjectCCP_SPEC

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     JDAEPTMemoCCP ();
     virtual ~JDAEPTMemoCCP ();

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#ListExtractFormats
     */
     //CATLISTP(CATFormat) ListExtractFormats () const ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#BoundaryExtract
     */
     //int BoundaryExtract (ListOfVarBaseUnknown&  ioObjectsAlreadyInBoundary  , const ListOfVarBaseUnknown*  iObjectsToAdd =NULL , const CATFormat*  iAnImposedFormat =NULL) const ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#Extract
     */
     //VarBaseUnknown Extract (ListOfVarBaseUnknown&  iObjectToCopy  , const CATFormat*  iAnImposedFormat =NULL) const ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#ListPasteFormats
     */
     //CATLISTP(CATFormat) ListPasteFormats () const ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#Paste
     */
     //ListOfVarBaseUnknown Paste (ListOfVarBaseUnknown&  iObjectToCopy  , ListOfVarBaseUnknown*  iToCurObjects =NULL , const CATFormat*  iAnImposedFormat =NULL) ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#Create
     */
     //int Create (CATBaseUnknown_Associations&  ioAssociationOfObjects  , const CATFormat*  an_imposed_format =NULL) ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#Update
     */
     int Update (CATBaseUnknown_Associations&  ioAssociationOfObjects  , const CATFormat*  iAnImposedFormat =NULL , ListOfVarBaseUnknown*  iToCurObjects =NULL) ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#ListLinkFormats
     */
     //CATLISTP(CATFormat) ListLinkFormats () const ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#Link
     */
     //ListOfVarBaseUnknown Link (ListOfVarBaseUnknown&  object_to_link  , ListOfVarBaseUnknown*  to_cur_objects =NULL , const CATFormat*  an_imposed_format =NULL) ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#ListRemoveFormats
     */
     //CATLISTP(CATFormat) ListRemoveFormats () const ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#BoundaryRemove
     */
     //int BoundaryRemove (ListOfVarBaseUnknown&  ioObjectsAlreadyInBoundary  , const ListOfVarBaseUnknown*  iObjectsToRemove =NULL , const CATFormat*  iAnImposedFormat =NULL) const ;

    /**
     * Implements a function from an interface.
     * @href CATICutAndPastable#Remove
     */
     //int Remove (ListOfVarBaseUnknown&  iObjectToRemove  , const CATFormat*  iAnImposedFormat =NULL) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  JDAEPTMemoCCP (JDAEPTMemoCCP &);
  JDAEPTMemoCCP& operator=(JDAEPTMemoCCP&);

};

//-----------------------------------------------------------------------

#endif
