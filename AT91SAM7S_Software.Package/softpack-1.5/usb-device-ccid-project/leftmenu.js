function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5514\" class=\"headerLeftMenuInActive\"><a id=\"aID5514\" href=\"#\" OnMouseOver=\"link('_dir','usbmi_devicemi_ccidmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">usb-device-ccid-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5632\" class=\"leftMenuInActive\"><a id=\"aID5632\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
