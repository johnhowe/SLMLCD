function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5516\" class=\"headerLeftMenuInActive\"><a id=\"aID5516\" href=\"#\" OnMouseOver=\"link('_dir','usbmi_devicemi_compositemi_cdchidmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">usb-device-composite-cdchid-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5634\" class=\"leftMenuInActive\"><a id=\"aID5634\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
