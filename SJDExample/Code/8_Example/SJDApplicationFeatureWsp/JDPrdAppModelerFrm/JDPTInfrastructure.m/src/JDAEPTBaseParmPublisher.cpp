// COPYRIGHT Dassault Systemes 2009
//===================================================================
//
// JDAEPTBaseParmPublisher.cpp
// Provide implementation to interface
//    CATIParmPublisher
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
//===================================================================
#include "JDAEPTBaseParmPublisher.h"

#include "CATIDescendants.h"
#include "CATListOfCATUnicodeString.h"
#include "CATISpecAttrKey.h"
#include "CATISpecAttrAccess.h"
//#include "CATICkeParm.h"

#include "iostream.h"

 
CATImplementClass(JDAEPTBaseParmPublisher,
                  DataExtension,
                  CATBaseUnknown,
                  JDAPTBase );
 

//-----------------------------------------------------------------------------
// JDAEPTBaseParmPublisher : constructor
//-----------------------------------------------------------------------------
JDAEPTBaseParmPublisher::JDAEPTBaseParmPublisher():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// JDAEPTBaseParmPublisher : destructor
//-----------------------------------------------------------------------------
JDAEPTBaseParmPublisher::~JDAEPTBaseParmPublisher()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIParmPublisher.h"
TIE_CATIParmPublisher( JDAEPTBaseParmPublisher);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATIParmPublisher::Append
//-----------------------------------------------------------------------------
void JDAEPTBaseParmPublisher::Append (const CATISpecObject_var &  iKBwareObject )
{

	//cout <<"==> Now we are in JDAEPTBaseParmPublisher::Append  !" << endl;

	//This method is used to attach new knowledgeware objects like parameters to
	// our feature
	//We use CATIDescendants to aggregate the feature
	
	HRESULT hr; 
	CATIDescendants *piDescendant = NULL;
	hr = this->QueryInterface(IID_CATIDescendants, (void**) &piDescendant);
	if (SUCCEEDED(hr) && piDescendant) {
		piDescendant->Append(iKBwareObject);
		piDescendant->Release();
		piDescendant = NULL;
	}
	else
		cout << "  ==> Get CATIDescendants error !" << endl;
	
	//cout <<"==> Now end JDAEPTBaseParmPublisher::Append  !" << endl;

   return;
}

//-----------------------------------------------------------------------------
// Implements CATIParmPublisher::RemoveChild
//-----------------------------------------------------------------------------
void JDAEPTBaseParmPublisher::RemoveChild (const CATISpecObject_var &  iKBwareObject )
{
	//This method is used to remove an knowledgeware object from our feature
	//We use CATIDescendants to aggregate the feature
	//cout<<"JDAEPTBaseParmPublisher::RemoveChild"<<endl;

	//cout <<"==> Now we are in JDAEPTBaseParmPublisher::RemoveChild  !" << endl;

	HRESULT hr; 
	CATIDescendants *piDescendant = NULL;
	hr = this->QueryInterface(IID_CATIDescendants, (void**) &piDescendant);
	if (SUCCEEDED(hr) && piDescendant) {
		piDescendant->RemoveChild(iKBwareObject);
		piDescendant->Release();
		piDescendant = NULL;
	}
	else
		cout << "  ==> Get CATIDescendants error !" << endl;

	//cout <<"==> Now end JDAEPTBaseParmPublisher::RemoveChild  !" << endl;


   return;
}

//-----------------------------------------------------------------------------
// Implements CATIParmPublisher::GetDirectChildren
//-----------------------------------------------------------------------------
void JDAEPTBaseParmPublisher::GetDirectChildren (CATClassId  iIntfName , CATListValCATISpecObject_var & iListFound)
{
	//This method returns the list of knowledgeware objects implementing the 
	// interface iIntfName and that are published by our feature
	// It may be built in specifications (text, length ...), but it may also be objects 
	// added by the user later on.

	//cout <<"==> Now we are in JDAEPTBaseParmPublisher::GetDirectChildren  !" << endl;

	HRESULT hr; 
	CATIDescendants *piDescendant = NULL;
	hr = this->QueryInterface(IID_CATIDescendants, (void**) &piDescendant);
	if (SUCCEEDED(hr) && piDescendant) {
		piDescendant->GetDirectChildren(iIntfName, iListFound);
		//possibility to parse the list to remove non published objects
		piDescendant->Release();
		piDescendant = NULL;
	}
	else
		cout << "  ==> Get CATIDescendants error !" << endl;

	//cout <<"==> Now end JDAEPTBaseParmPublisher::GetDirectChildren  !" << endl;

   return;
}

//-----------------------------------------------------------------------------
// Implements CATIParmPublisher::GetAllChildren
//-----------------------------------------------------------------------------
void JDAEPTBaseParmPublisher::GetAllChildren (CATClassId  iIntfName , CATListValCATISpecObject_var & ListFound)
{

	//cout <<"==> Now we are in JDAEPTBaseParmPublisher::GetAllChildren  !" << endl;

	//Search recursively for knowledgeware objects that are published by our
	// feature or by one of its descendant.
	//cout<<"JDAEPTBaseParmPublisher::GetAllChildren"<<endl;
	HRESULT hr; 
	CATIDescendants *piDescendant = NULL;
	hr = this->QueryInterface(IID_CATIDescendants, (void**) &piDescendant);
	if (SUCCEEDED(hr) && piDescendant) {
		piDescendant->GetAllChildren(iIntfName, ListFound);
		//possibility to parse the list to remove non published objects
		piDescendant->Release();
		piDescendant = NULL;
	}
	else
		cout << "  ==> Get CATIDescendants error !" << endl;

	//cout <<"==> Now end JDAEPTBaseParmPublisher::GetAllChildren  !" << endl;

   return;
}

//-----------------------------------------------------------------------------
// Implements CATIParmPublisher::AllowUserAppend
//-----------------------------------------------------------------------------
boolean JDAEPTBaseParmPublisher::AllowUserAppend () const
{
	//Informs the application, that our object implements the methods
	// Append and RemoveChild and that it is possible to attach new 
	// knowledgeware object on our feature 
	// (like parameters in the Parameter Editor panel).
	//
	//cout<<"JDAEPTBaseParmPublisher::AllowUserAppend"<<endl;

	//cout <<"==> Now we are in JDAEPTBaseParmPublisher::AllowUserAppend  !" << endl;
	return true;


}

//-----------------------------------------------------------------------------
// Implements CATIParmPublisher::GetContainer
//-----------------------------------------------------------------------------
CATIContainer_var JDAEPTBaseParmPublisher::GetContainer ()
{
	//cout <<"==> Now we are in JDAEPTBaseParmPublisher::GetContainer  !" << endl;

	//This method is used to know the container of a non feature object
	// there is no need to implement it in this case
	//cout<<"JDAEPTBaseParmPublisher::GetContainer"<<endl;
	CATIContainer_var retour=NULL_var;
	CATISpecObject_var spec(this);
	if (!!spec)
		retour = spec->GetFeatContainer();

	//cout <<"==> Now end JDAEPTBaseParmPublisher::GetContainer  !" << endl;
	return retour;
}

//-----------------------------------------------------------------------------
// Implements CATIParmPublisher::VisitChildren
//-----------------------------------------------------------------------------
void JDAEPTBaseParmPublisher::VisitChildren (CATIVisitor*  iVisitor , const int  recur )
{
	//This method is planned to replace GetDirectChildren and GetAllChildren
	// from release R7.

	//This generic implementation of VisitChildren does not take into account
	// the new literal. To take new literal into account you must now the
	// publisher modilisation and where to search for as they can not be pointed
	// on by a tk_list of tk_component
	//cout <<"==> Now we are in JDAEPTBaseParmPublisher::VisitChildren  !" << endl;
	if (iVisitor) {
		CATLISTV(CATISpecObject_var) liste;
		GetDirectChildren(CATISpecObject::ClassName(), liste);

		int i, size;
		size = liste.Size();

		cout << "  ==> The number of direct children: " << size << endl;

		for(i = 1; i <= size; i++)
		{
			CATISpecObject_var spec = liste[i];
			if (!!spec)
			{
				HRESULT hr = iVisitor->Visit(spec);
				if (!SUCCEEDED(hr))
				{
					// c'est le cas d'arret de la recherche
					//cout <<"  ==> JDAEPTBaseParmPublisher::VisitChildren  error !" << endl;
					return;
				}
			}
		}

		if (recur) {
			for(i = 1; i <= size; i++) {
				CATIParmPublisher_var publisher = liste[i];
				if (!!publisher)
				{
					publisher->VisitChildren(iVisitor, recur);
				}
			}
		}
	} 
	//cout <<"==> Now end JDAEPTBaseParmPublisher::VisitChildren  !" << endl;


   return;
}
