# COPYRIGHT Dassault Systemes 2012
#======================================================================
# Imakefile for module SJDRelinkDrawingPartM.m
#======================================================================
#
#  Jul 2012  Creation: Code generated by the CAA wizard  THINKPAD
#======================================================================
#
# LOAD MODULE 
#
BUILT_OBJECT_TYPE=LOAD MODULE 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES) CATObjectModelerBase CATDraftingInterfaces \
			CATObjectSpecsModeler CATxPDMInterfaces CATMathematics \
			CATProductStructure1 

# System dependant variables
#
OS = AIX
#
OS = HP-UX
#
OS = IRIX
#
OS = SunOS
#
OS = Windows_NT
