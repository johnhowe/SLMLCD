function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5494\" class=\"headerLeftMenuInActive\"><a id=\"aID5494\" href=\"#\" OnMouseOver=\"link('_dir','core0',this)\" class=\"leftMenuLinkHeadInActive\">core</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5411\" class=\"leftMenuInActive\"><a id=\"aID5411\" href=\"#\" OnMouseOver=\"link('_page','Endpointstates0',this)\" class=\"leftMenuLinkInActive\">Endpoint states</a></div>\n");
document.write("<div id=\"divID5410\" class=\"leftMenuInActive\"><a id=\"aID5410\" href=\"#\" OnMouseOver=\"link('_page','UDPregisterfieldvalues0',this)\" class=\"leftMenuLinkInActive\">UDP register field values</a></div>\n");
document.write("<div id=\"divID5412\" class=\"leftMenuInActive\"><a id=\"aID5412\" href=\"#\" OnMouseOver=\"link('_page','UDP_CSRregisteraccess0',this)\" class=\"leftMenuLinkInActive\">UDP_CSR register access</a></div>\n");
document.write("<div id=\"divID5407\" class=\"leftMenuInActive\"><a id=\"aID5407\" href=\"#\" OnMouseOver=\"link('_page','USBdeviceAPIreturnvalues0',this)\" class=\"leftMenuLinkInActive\">USB device API return values</a></div>\n");
document.write("<div id=\"divID5409\" class=\"leftMenuInActive\"><a id=\"aID5409\" href=\"#\" OnMouseOver=\"link('_page','USBdeviceLEDs0',this)\" class=\"leftMenuLinkInActive\">USB device LEDs</a></div>\n");
document.write("<div id=\"divID5408\" class=\"leftMenuInActive\"><a id=\"aID5408\" href=\"#\" OnMouseOver=\"link('_page','USBdevicestates0',this)\" class=\"leftMenuLinkInActive\">USB device states</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5592\" class=\"leftMenuInActive\"><a id=\"aID5592\" href=\"#\" OnMouseOver=\"link('_unit','USBD_h0',this)\" class=\"leftMenuLinkInActive\">USBD.h</a></div>\n");
document.write("<div id=\"divID5593\" class=\"leftMenuInActive\"><a id=\"aID5593\" href=\"#\" OnMouseOver=\"link('_unit','USBD_UDP_c0',this)\" class=\"leftMenuLinkInActive\">USBD_UDP.c</a></div>\n");
document.write("<div id=\"divID5594\" class=\"leftMenuInActive\"><a id=\"aID5594\" href=\"#\" OnMouseOver=\"link('_unit','USBDCallbacks_h0',this)\" class=\"leftMenuLinkInActive\">USBDCallbacks.h</a></div>\n");
document.write("<div id=\"divID5595\" class=\"leftMenuInActive\"><a id=\"aID5595\" href=\"#\" OnMouseOver=\"link('_unit','USBDDriver_h0',this)\" class=\"leftMenuLinkInActive\">USBDDriver.h</a></div>\n");
document.write("<div id=\"divID5596\" class=\"leftMenuInActive\"><a id=\"aID5596\" href=\"#\" OnMouseOver=\"link('_unit','USBDDriverCallbacks_h0',this)\" class=\"leftMenuLinkInActive\">USBDDriverCallbacks.h</a></div>\n");
document.write("<div id=\"divID5597\" class=\"leftMenuInActive\"><a id=\"aID5597\" href=\"#\" OnMouseOver=\"link('_unit','USBDDriverDescriptors_h0',this)\" class=\"leftMenuLinkInActive\">USBDDriverDescriptors.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
