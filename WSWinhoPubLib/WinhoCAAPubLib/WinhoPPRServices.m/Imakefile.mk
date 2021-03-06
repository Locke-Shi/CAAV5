# COPYRIGHT Dassault Systemes 2015
#======================================================================
# Imakefile for module WinhoPPRServices.m
#======================================================================
#
#  Apr 2015  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0GROUP CATProcessInterfaces CATObjectSpecsModeler CATMecModInterfaces CATProductStructure1 CATTopologicalObjects CATMathematics \
CATMechanicalModeler CATInteractiveInterfaces CATObjectModelerBase CATApplicationFrame KnowledgeItf CATViz CATVisualization CATProductStructureInterfaces CATInfInterfaces \
WinhoUniversalServices WinhoVisualServices WinhoCGMServices\
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)

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
