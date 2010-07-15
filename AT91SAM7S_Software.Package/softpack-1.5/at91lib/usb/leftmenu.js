function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5500\" class=\"headerLeftMenuInActive\"><a id=\"aID5500\" href=\"#\" OnMouseOver=\"link('_dir','usb0',this)\" class=\"leftMenuLinkHeadInActive\">usb</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5486\" class=\"leftMenuInActive\"><a id=\"aID5486\" href=\"#\" OnMouseOver=\"link('_dir','common/common0',this)\" class=\"leftMenuLinkInActive\">common</a></div>\n");
document.write("<div id=\"divID5495\" class=\"leftMenuInActive\"><a id=\"aID5495\" href=\"#\" OnMouseOver=\"link('_dir','device/device0',this)\" class=\"leftMenuLinkInActive\">device</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5451\" class=\"leftMenuInActive\"><a id=\"aID5451\" href=\"#\" OnMouseOver=\"link('_page','AT91USBdeviceframework0',this)\" class=\"leftMenuLinkInActive\">AT91 USB device framework</a></div>\n");
document.write("<div id=\"divID5455\" class=\"leftMenuInActive\"><a id=\"aID5455\" href=\"#\" OnMouseOver=\"link('_page','USBDeviceEnumeration0',this)\" class=\"leftMenuLinkInActive\">USB Device Enumeration</a></div>\n");
document.write("<div id=\"divID5452\" class=\"leftMenuInActive\"><a id=\"aID5452\" href=\"#\" OnMouseOver=\"link('_page','USBDeviceFrameworkArchitecture0',this)\" class=\"leftMenuLinkInActive\">USB Device Framework Architecture</a></div>\n");
document.write("<div id=\"divID5453\" class=\"leftMenuInActive\"><a id=\"aID5453\" href=\"#\" OnMouseOver=\"link('_page','USBDeviceFrameworkDescription0',this)\" class=\"leftMenuLinkInActive\">USB Device Framework Description</a></div>\n");
document.write("<div id=\"divID5454\" class=\"leftMenuInActive\"><a id=\"aID5454\" href=\"#\" OnMouseOver=\"link('_page','USBDeviceFrameworkUsage0',this)\" class=\"leftMenuLinkInActive\">USB Device Framework Usage</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
