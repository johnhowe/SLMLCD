function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5486\" class=\"headerLeftMenuInActive\"><a id=\"aID5486\" href=\"#\" OnMouseOver=\"link('_dir','common0',this)\" class=\"leftMenuLinkHeadInActive\">common</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5485\" class=\"leftMenuInActive\"><a id=\"aID5485\" href=\"#\" OnMouseOver=\"link('_dir','cdc/cdc0',this)\" class=\"leftMenuLinkInActive\">cdc</a></div>\n");
document.write("<div id=\"divID5487\" class=\"leftMenuInActive\"><a id=\"aID5487\" href=\"#\" OnMouseOver=\"link('_dir','core/core0',this)\" class=\"leftMenuLinkInActive\">core</a></div>\n");
document.write("<div id=\"divID5488\" class=\"leftMenuInActive\"><a id=\"aID5488\" href=\"#\" OnMouseOver=\"link('_dir','hid/hid0',this)\" class=\"leftMenuLinkInActive\">hid</a></div>\n");
document.write("<div id=\"divID5489\" class=\"leftMenuInActive\"><a id=\"aID5489\" href=\"#\" OnMouseOver=\"link('_dir','massstorage/massstorage0',this)\" class=\"leftMenuLinkInActive\">massstorage</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
