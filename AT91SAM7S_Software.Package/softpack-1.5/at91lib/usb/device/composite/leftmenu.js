function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5492\" class=\"headerLeftMenuInActive\"><a id=\"aID5492\" href=\"#\" OnMouseOver=\"link('_dir','composite0',this)\" class=\"leftMenuLinkHeadInActive\">composite</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5493\" class=\"leftMenuInActive\"><a id=\"aID5493\" href=\"#\" OnMouseOver=\"link('_dir','drv/drv0',this)\" class=\"leftMenuLinkInActive\">drv</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5406\" class=\"leftMenuInActive\"><a id=\"aID5406\" href=\"#\" OnMouseOver=\"link('_page','MSinterfaceam_endpointdescriptorsettings0',this)\" class=\"leftMenuLinkInActive\">MS interface & endpoint descriptor settings</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5590\" class=\"leftMenuInActive\"><a id=\"aID5590\" href=\"#\" OnMouseOver=\"link('_unit','COMPOSITEDDriver_h0',this)\" class=\"leftMenuLinkInActive\">COMPOSITEDDriver.h</a></div>\n");
document.write("<div id=\"divID5591\" class=\"leftMenuInActive\"><a id=\"aID5591\" href=\"#\" OnMouseOver=\"link('_unit','MSDDFunctionDriver_h0',this)\" class=\"leftMenuLinkInActive\">MSDDFunctionDriver.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
