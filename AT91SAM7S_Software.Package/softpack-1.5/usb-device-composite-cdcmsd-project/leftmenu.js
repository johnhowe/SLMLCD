function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5517\" class=\"headerLeftMenuInActive\"><a id=\"aID5517\" href=\"#\" OnMouseOver=\"link('_dir','usbmi_devicemi_compositemi_cdcmsdmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">usb-device-composite-cdcmsd-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5635\" class=\"leftMenuInActive\"><a id=\"aID5635\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
