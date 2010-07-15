function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5485\" class=\"headerLeftMenuInActive\"><a id=\"aID5485\" href=\"#\" OnMouseOver=\"link('_dir','cdc0',this)\" class=\"leftMenuLinkHeadInActive\">cdc</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5347\" class=\"leftMenuInActive\"><a id=\"aID5347\" href=\"#\" OnMouseOver=\"link('_page','CDCACMCapabilities0',this)\" class=\"leftMenuLinkInActive\">CDC ACM Capabilities</a></div>\n");
document.write("<div id=\"divID5348\" class=\"leftMenuInActive\"><a id=\"aID5348\" href=\"#\" OnMouseOver=\"link('_page','CDCCallManagementCapabilities0',this)\" class=\"leftMenuLinkInActive\">CDC CallManagement Capabilities</a></div>\n");
document.write("<div id=\"divID5349\" class=\"leftMenuInActive\"><a id=\"aID5349\" href=\"#\" OnMouseOver=\"link('_page','CDCCommunicationInterfaceValues0',this)\" class=\"leftMenuLinkInActive\">CDC Communication Interface Values</a></div>\n");
document.write("<div id=\"divID5350\" class=\"leftMenuInActive\"><a id=\"aID5350\" href=\"#\" OnMouseOver=\"link('_page','CDCDataInterfaceValues0',this)\" class=\"leftMenuLinkInActive\">CDC Data Interface Values</a></div>\n");
document.write("<div id=\"divID5354\" class=\"leftMenuInActive\"><a id=\"aID5354\" href=\"#\" OnMouseOver=\"link('_page','CDCDescriptorSubtypes0',this)\" class=\"leftMenuLinkInActive\">CDC Descriptor Subtypes</a></div>\n");
document.write("<div id=\"divID5353\" class=\"leftMenuInActive\"><a id=\"aID5353\" href=\"#\" OnMouseOver=\"link('_page','CDCDescriptroTypes0',this)\" class=\"leftMenuLinkInActive\">CDC Descriptro Types</a></div>\n");
document.write("<div id=\"divID5351\" class=\"leftMenuInActive\"><a id=\"aID5351\" href=\"#\" OnMouseOver=\"link('_page','CDCDeviceDescriptorValues0',this)\" class=\"leftMenuLinkInActive\">CDC Device Descriptor Values</a></div>\n");
document.write("<div id=\"divID5357\" class=\"leftMenuInActive\"><a id=\"aID5357\" href=\"#\" OnMouseOver=\"link('_page','CDCLineCodingParityCheckings0',this)\" class=\"leftMenuLinkInActive\">CDC LineCoding ParityCheckings</a></div>\n");
document.write("<div id=\"divID5356\" class=\"leftMenuInActive\"><a id=\"aID5356\" href=\"#\" OnMouseOver=\"link('_page','CDCLineCodingStopBits0',this)\" class=\"leftMenuLinkInActive\">CDC LineCoding StopBits</a></div>\n");
document.write("<div id=\"divID5355\" class=\"leftMenuInActive\"><a id=\"aID5355\" href=\"#\" OnMouseOver=\"link('_page','CDCRequestCodes0',this)\" class=\"leftMenuLinkInActive\">CDC Request Codes</a></div>\n");
document.write("<div id=\"divID5352\" class=\"leftMenuInActive\"><a id=\"aID5352\" href=\"#\" OnMouseOver=\"link('_page','CDCSpecificationReleaseNumbers0',this)\" class=\"leftMenuLinkInActive\">CDC Specification Release Numbers</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5550\" class=\"leftMenuInActive\"><a id=\"aID5550\" href=\"#\" OnMouseOver=\"link('_unit','CDCAbstractControlManagementDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCAbstractControlManagementDescriptor.h</a></div>\n");
document.write("<div id=\"divID5551\" class=\"leftMenuInActive\"><a id=\"aID5551\" href=\"#\" OnMouseOver=\"link('_unit','CDCCallManagementDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCCallManagementDescriptor.h</a></div>\n");
document.write("<div id=\"divID5552\" class=\"leftMenuInActive\"><a id=\"aID5552\" href=\"#\" OnMouseOver=\"link('_unit','CDCCommunicationInterfaceDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCCommunicationInterfaceDescriptor.h</a></div>\n");
document.write("<div id=\"divID5553\" class=\"leftMenuInActive\"><a id=\"aID5553\" href=\"#\" OnMouseOver=\"link('_unit','CDCDataInterfaceDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCDataInterfaceDescriptor.h</a></div>\n");
document.write("<div id=\"divID5554\" class=\"leftMenuInActive\"><a id=\"aID5554\" href=\"#\" OnMouseOver=\"link('_unit','CDCDeviceDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCDeviceDescriptor.h</a></div>\n");
document.write("<div id=\"divID5555\" class=\"leftMenuInActive\"><a id=\"aID5555\" href=\"#\" OnMouseOver=\"link('_unit','CDCGenericDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCGenericDescriptor.h</a></div>\n");
document.write("<div id=\"divID5556\" class=\"leftMenuInActive\"><a id=\"aID5556\" href=\"#\" OnMouseOver=\"link('_unit','CDCGenericRequest_h0',this)\" class=\"leftMenuLinkInActive\">CDCGenericRequest.h</a></div>\n");
document.write("<div id=\"divID5557\" class=\"leftMenuInActive\"><a id=\"aID5557\" href=\"#\" OnMouseOver=\"link('_unit','CDCHeaderDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCHeaderDescriptor.h</a></div>\n");
document.write("<div id=\"divID5558\" class=\"leftMenuInActive\"><a id=\"aID5558\" href=\"#\" OnMouseOver=\"link('_unit','CDCLineCoding_h0',this)\" class=\"leftMenuLinkInActive\">CDCLineCoding.h</a></div>\n");
document.write("<div id=\"divID5559\" class=\"leftMenuInActive\"><a id=\"aID5559\" href=\"#\" OnMouseOver=\"link('_unit','CDCSetControlLineStateRequest_h0',this)\" class=\"leftMenuLinkInActive\">CDCSetControlLineStateRequest.h</a></div>\n");
document.write("<div id=\"divID5560\" class=\"leftMenuInActive\"><a id=\"aID5560\" href=\"#\" OnMouseOver=\"link('_unit','CDCUnionDescriptor_h0',this)\" class=\"leftMenuLinkInActive\">CDCUnionDescriptor.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
