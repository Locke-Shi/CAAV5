# COPYRIGHT Dassault Systemes 2009
#======================================================================
# Imakefile for module JDPTInfrastructure.m
#======================================================================
#
#  Apr 2009  Creation: Code generated by the CAA wizard  LuJun
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0FM JS0GROUP JDAPointItfCPP JDAPointInterfacesUUID  \
AD0XXBAS ObjectModelerBaseUUID  \
ON0MAIN  \
CATVisualization CATVisUUID  \
KnowledgeItf KnowledgeInterfacesUUID  \
CP0SPEC CP0CLIP  \
AC0SPEXT ObjectSpecsModelerUUID  \
AC0SPBAS  \
CD0FRAME CATAfrUUID  \
CATOmnMain ObjectModelerNavigatorUUID  \
ApplicationFrame 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES) KnowledgeItf CATObjectSpecsModeler \
			 CATApplicationFrame \
			 JS0GROUP \
			 CATProductStructure1 \
			 CATObjectModelerBase \
			 CATObjectModelerNavigator \
			 CATVisualization \
			 CATViz \
			CATProductStructure1 ObjectModelerSystem 

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
CL = /EHsc