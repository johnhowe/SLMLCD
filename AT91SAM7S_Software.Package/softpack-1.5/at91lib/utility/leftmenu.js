function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5501\" class=\"headerLeftMenuInActive\"><a id=\"aID5501\" href=\"#\" OnMouseOver=\"link('_dir','utility0',this)\" class=\"leftMenuLinkHeadInActive\">utility</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5615\" class=\"leftMenuInActive\"><a id=\"aID5615\" href=\"#\" OnMouseOver=\"link('_unit','assert_h0',this)\" class=\"leftMenuLinkInActive\">assert.h</a></div>\n");
document.write("<div id=\"divID5616\" class=\"leftMenuInActive\"><a id=\"aID5616\" href=\"#\" OnMouseOver=\"link('_unit','led_h0',this)\" class=\"leftMenuLinkInActive\">led.h</a></div>\n");
document.write("<div id=\"divID5617\" class=\"leftMenuInActive\"><a id=\"aID5617\" href=\"#\" OnMouseOver=\"link('_unit','retarget_c0',this)\" class=\"leftMenuLinkInActive\">retarget.c</a></div>\n");
document.write("<div id=\"divID5618\" class=\"leftMenuInActive\"><a id=\"aID5618\" href=\"#\" OnMouseOver=\"link('_unit','stdio_c0',this)\" class=\"leftMenuLinkInActive\">stdio.c</a></div>\n");
document.write("<div id=\"divID5619\" class=\"leftMenuInActive\"><a id=\"aID5619\" href=\"#\" OnMouseOver=\"link('_unit','string_c0',this)\" class=\"leftMenuLinkInActive\">string.c</a></div>\n");
document.write("<div id=\"divID5620\" class=\"leftMenuInActive\"><a id=\"aID5620\" href=\"#\" OnMouseOver=\"link('_unit','trace_h0',this)\" class=\"leftMenuLinkInActive\">trace.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
