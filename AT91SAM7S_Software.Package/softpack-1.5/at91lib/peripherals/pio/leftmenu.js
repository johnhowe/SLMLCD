function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5476\" class=\"headerLeftMenuInActive\"><a id=\"aID5476\" href=\"#\" OnMouseOver=\"link('_dir','pio0',this)\" class=\"leftMenuLinkHeadInActive\">pio</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5542\" class=\"leftMenuInActive\"><a id=\"aID5542\" href=\"#\" OnMouseOver=\"link('_unit','pio_h0',this)\" class=\"leftMenuLinkInActive\">pio.h</a></div>\n");
document.write("<div id=\"divID5543\" class=\"leftMenuInActive\"><a id=\"aID5543\" href=\"#\" OnMouseOver=\"link('_unit','pio_it_h0',this)\" class=\"leftMenuLinkInActive\">pio_it.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
