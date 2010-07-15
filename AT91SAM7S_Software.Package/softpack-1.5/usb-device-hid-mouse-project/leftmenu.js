function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5521\" class=\"headerLeftMenuInActive\"><a id=\"aID5521\" href=\"#\" OnMouseOver=\"link('_dir','usbmi_devicemi_hidmi_mousemi_project0',this)\" class=\"leftMenuLinkHeadInActive\">usb-device-hid-mouse-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5639\" class=\"leftMenuInActive\"><a id=\"aID5639\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
