function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5480\" class=\"headerLeftMenuInActive\"><a id=\"aID5480\" href=\"#\" OnMouseOver=\"link('_dir','rtt0',this)\" class=\"leftMenuLinkHeadInActive\">rtt</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5546\" class=\"leftMenuInActive\"><a id=\"aID5546\" href=\"#\" OnMouseOver=\"link('_unit','rtt_h0',this)\" class=\"leftMenuLinkInActive\">rtt.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
