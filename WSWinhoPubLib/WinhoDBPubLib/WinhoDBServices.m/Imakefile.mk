# COPYRIGHT �Ϻ������Ϣ�������޹�˾ 2017
#======================================================================
# Imakefile for module WinhoDBServices.m
#======================================================================
#
#  Jun 2017  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
WinhoUniversalServices \
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