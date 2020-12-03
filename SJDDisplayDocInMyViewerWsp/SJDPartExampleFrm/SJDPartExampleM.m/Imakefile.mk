# COPYRIGHT Dassault Systemes 2015
#======================================================================
# Imakefile for module SJDPartExampleM.m
#======================================================================
#
#  Jan 2015  Creation: Code generated by the CAA wizard  LuJunHome
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
	JS0GROUP JS0FM DI0PANV2   \
	CATDialogEngine  
	
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES) CATApplicationFrame \
			 CATDialogEngine \
			 JS0GROUP \
			 CATMathematics \
			CATVisualization CATViz CATGitInterfaces CATObjectModelerBase \
			CATMecModInterfaces CATVisualization CATObjectSpecsModeler 

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
