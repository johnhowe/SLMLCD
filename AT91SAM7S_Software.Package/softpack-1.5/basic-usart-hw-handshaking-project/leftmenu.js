function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5512\" class=\"headerLeftMenuInActive\"><a id=\"aID5512\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_usartmi_hwmi_handshakingmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-usart-hw-handshaking-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5630\" class=\"leftMenuInActive\"><a id=\"aID5630\" href=\"#\" OnMouseOver=\"link('_unit','printf_usart_c0',this)\" class=\"leftMenuLinkInActive\">printf_usart.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
