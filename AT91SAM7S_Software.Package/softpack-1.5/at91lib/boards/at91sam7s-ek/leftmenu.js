function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5458\" class=\"headerLeftMenuInActive\"><a id=\"aID5458\" href=\"#\" OnMouseOver=\"link('_dir','at91sam7smi_ek0',this)\" class=\"leftMenuLinkHeadInActive\">at91sam7s-ek</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5457\" class=\"leftMenuInActive\"><a id=\"aID5457\" href=\"#\" OnMouseOver=\"link('_dir','at91sam7s128/at91sam7s1280',this)\" class=\"leftMenuLinkInActive\">at91sam7s128</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5338\" class=\"leftMenuInActive\"><a id=\"aID5338\" href=\"#\" OnMouseOver=\"link('_page','SAM7Smi_EKmi_Externalcomponents0',this)\" class=\"leftMenuLinkInActive\">SAM7S-EK - External components</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5525\" class=\"leftMenuInActive\"><a id=\"aID5525\" href=\"#\" OnMouseOver=\"link('_unit','board_h0',this)\" class=\"leftMenuLinkInActive\">board.h</a></div>\n");
document.write("<div id=\"divID5526\" class=\"leftMenuInActive\"><a id=\"aID5526\" href=\"#\" OnMouseOver=\"link('_unit','board_lowlevel_h0',this)\" class=\"leftMenuLinkInActive\">board_lowlevel.h</a></div>\n");
document.write("<div id=\"divID5527\" class=\"leftMenuInActive\"><a id=\"aID5527\" href=\"#\" OnMouseOver=\"link('_unit','board_memories_h0',this)\" class=\"leftMenuLinkInActive\">board_memories.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
