function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5463\" class=\"headerLeftMenuInActive\"><a id=\"aID5463\" href=\"#\" OnMouseOver=\"link('_dir','drivers0',this)\" class=\"leftMenuLinkHeadInActive\">drivers</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5462\" class=\"leftMenuInActive\"><a id=\"aID5462\" href=\"#\" OnMouseOver=\"link('_dir','async/async0',this)\" class=\"leftMenuLinkInActive\">async</a></div>\n");
document.write("<div id=\"divID5464\" class=\"leftMenuInActive\"><a id=\"aID5464\" href=\"#\" OnMouseOver=\"link('_dir','twi/twi0',this)\" class=\"leftMenuLinkInActive\">twi</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
