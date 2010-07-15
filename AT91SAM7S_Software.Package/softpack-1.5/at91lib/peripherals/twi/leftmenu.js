function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5483\" class=\"headerLeftMenuInActive\"><a id=\"aID5483\" href=\"#\" OnMouseOver=\"link('_dir','twi0',this)\" class=\"leftMenuLinkHeadInActive\">twi</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5548\" class=\"leftMenuInActive\"><a id=\"aID5548\" href=\"#\" OnMouseOver=\"link('_unit','twi_c0',this)\" class=\"leftMenuLinkInActive\">twi.c</a></div>\n");
document.write("<div id=\"divID5549\" class=\"leftMenuInActive\"><a id=\"aID5549\" href=\"#\" OnMouseOver=\"link('_unit','twi_h0',this)\" class=\"leftMenuLinkInActive\">twi.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
