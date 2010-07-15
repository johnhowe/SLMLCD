function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5497\" class=\"headerLeftMenuInActive\"><a id=\"aID5497\" href=\"#\" OnMouseOver=\"link('_dir','hidmi_mouse0',this)\" class=\"leftMenuLinkHeadInActive\">hid-mouse</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5426\" class=\"leftMenuInActive\"><a id=\"aID5426\" href=\"#\" OnMouseOver=\"link('_page','HIDMouseButtonbitmaps0',this)\" class=\"leftMenuLinkInActive\">HID Mouse Button bitmaps</a></div>\n");
document.write("<div id=\"divID5427\" class=\"leftMenuInActive\"><a id=\"aID5427\" href=\"#\" OnMouseOver=\"link('_page','HIDMouseDeviceDescriptorIDs0',this)\" class=\"leftMenuLinkInActive\">HID Mouse Device Descriptor IDs</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5603\" class=\"leftMenuInActive\"><a id=\"aID5603\" href=\"#\" OnMouseOver=\"link('_unit','HIDDMouseDriver_h0',this)\" class=\"leftMenuLinkInActive\">HIDDMouseDriver.h</a></div>\n");
document.write("<div id=\"divID5604\" class=\"leftMenuInActive\"><a id=\"aID5604\" href=\"#\" OnMouseOver=\"link('_unit','HIDDMouseDriverDescriptors_h0',this)\" class=\"leftMenuLinkInActive\">HIDDMouseDriverDescriptors.h</a></div>\n");
document.write("<div id=\"divID5605\" class=\"leftMenuInActive\"><a id=\"aID5605\" href=\"#\" OnMouseOver=\"link('_unit','HIDDMouseInputReport_h0',this)\" class=\"leftMenuLinkInActive\">HIDDMouseInputReport.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
