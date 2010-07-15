function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5469\" class=\"headerLeftMenuInActive\"><a id=\"aID5469\" href=\"#\" OnMouseOver=\"link('_dir','adc0',this)\" class=\"leftMenuLinkHeadInActive\">adc</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5536\" class=\"leftMenuInActive\"><a id=\"aID5536\" href=\"#\" OnMouseOver=\"link('_unit','adc_h0',this)\" class=\"leftMenuLinkInActive\">adc.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
