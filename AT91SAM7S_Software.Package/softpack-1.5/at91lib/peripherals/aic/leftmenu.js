function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5470\" class=\"headerLeftMenuInActive\"><a id=\"aID5470\" href=\"#\" OnMouseOver=\"link('_dir','aic0',this)\" class=\"leftMenuLinkHeadInActive\">aic</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5537\" class=\"leftMenuInActive\"><a id=\"aID5537\" href=\"#\" OnMouseOver=\"link('_unit','aic_h0',this)\" class=\"leftMenuLinkInActive\">aic.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
