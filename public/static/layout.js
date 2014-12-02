var term_t_color = "";
var term_bg_color="";
var dicToSend ={};
$(document).ready(function(){ 
	show_hide_LS();
	setup_layout_widget();
  $('#editor-container').hide();
  $('#theme_tab').hide();
  $('#machine_login_modal').modal('show');
  $('#theme_selector').change(function(){
    ace.edit("editor").setTheme("ace/theme/"+$(this).val());
  });
  $('[data-toggle="tooltip"]').tooltip({'placement': 'left'}); 
  socket_init();
  //Event handler to generate the folder List 
  $(document).on("generateLS", function() {
    var x = $(".fileItem");
    var length = x.length;
    if (x.length) {
      x.remove();
    }
    $('#dump span').each(function(i) {
    if ($(this).css('color') == 'rgb(85, 85, 255)') {
      $('#ls').add('<li class="fileItem"><a href="#">'+ $(this).text() +'</a></li>').appendTo('#ls');
      $(this).remove();
    }
    });

    //sending cd + dir upon clicking on one of the links in the folder list
    $('#ls li').each(function(i){
      $(this).click(function(){
         var socket = io();
         socket.emit('cmd', 'cd '+$(this).text());
         $("#wrapper").attr('class', "toggled");
      });
    });
  });

  //handling save
  $('#save').on('click', function() {
    var socket = io();
    var editor = ace.edit("editor");
    dicToSend.data = editor.getValue();
    socket.emit('saveFile',dicToSend);
  });
  $('#close').click(function() {closeEditor();});
});

function changeColors() {
	$('#container').css('background-color', term_bg_color);
	$('#std-out').css('background-color', term_bg_color);
	$('#std-in').css('background-color', term_bg_color);

	$('#std-out').css('color', term_t_color);
	$('#std-in').css('color', term_t_color);
}

function show_hide_LS() {

$("#menu-toggle").click(function(e) {
        e.preventDefault();
        $("#wrapper").toggleClass("toggled");
    });

}

//setting up the modal content layout
function setup_layout_widget() {

	$(function() {
  
    function hexFromRGB(r, g, b) {
    var hex = [
      r.toString( 16 ),
      g.toString( 16 ),
      b.toString( 16 )
    ];
    $.each( hex, function( nr, val ) {
      if ( val.length === 1 ) {
        hex[ nr ] = "0" + val;
      }
    });
    return hex.join( "" ).toUpperCase();
  }
  function refreshSwatch() {
    var red = $( "#red-1" ).slider( "value" ),
      green = $( "#green-1" ).slider( "value" ),
      blue = $( "#blue-1" ).slider( "value" ),
      hex = hexFromRGB( red, green, blue );
    $( "#swatch-1" ).css( "background-color", "#" + hex );
    term_bg_color = "#" + hex; 
    
  }
  $(function() {
    $( "#red-1, #green-1, #blue-1" ).slider({
      orientation: "horizontal",
      range: "min",
      max: 255,
      value: 127,
      slide: refreshSwatch,
      change: refreshSwatch
    });
    $( "#red-1" ).slider( "value", 0 );
    $( "#green-1" ).slider( "value", 0 );
    $( "#blue-1" ).slider( "value", 0 );
    
  });
  });

   $(function() {
  
    function hexFromRGB(r, g, b) {
    var hex = [
      r.toString( 16 ),
      g.toString( 16 ),
      b.toString( 16 )
    ];
    $.each( hex, function( nr, val ) {
      if ( val.length === 1 ) {
        hex[ nr ] = "0" + val;
      }
    });
    return hex.join( "" ).toUpperCase();
  }
  function refreshSwatch() {
    var red = $( "#red-2" ).slider( "value" ),
      green = $( "#green-2" ).slider( "value" ),
      blue = $( "#blue-2" ).slider( "value" ),
      hex = hexFromRGB( red, green, blue );
    $( "#swatch-2" ).css( "background-color", "#" + hex );
    term_t_color = "#" + hex; 
   	
  }
  $(function() {
    $( "#red-2, #green-2, #blue-2" ).slider({
      orientation: "horizontal",
      range: "min",
      max: 255,
      value: 127,
      slide: refreshSwatch,
      change: refreshSwatch
    });
    $( "#red-2" ).slider( "value", 255);
    $( "#green-2" ).slider( "value", 255);
    $( "#blue-2" ).slider( "value", 255 );
    
  });
  });
}

//Function that parses a string and checks if it is a directory or a file when ls --file-type is called on the terminal 
//This is used for creating the side bar menu
function createDirectoryElem(str) {
   var i = str.length - 1; 
   if (str[i] == '/') {
      var directory = str.slice(0,i);
      $('#ls').add('<li><a href="#">'+directory+'</a></li>').appendTo('#ls');
    }
    else {
      var array = str.split('.');
      var j = array.length - 1; 
      var extension = array[j]; 
    }
}

//setupace
function setupEditor(filePath) {
$('#theme_tab').show();
var editor = ace.edit("editor");
editor.setTheme("ace/theme/"+$('#theme_selector').val());
var modelist = ace.require("ace/ext/modelist");
var mode = modelist.getModeForPath(filePath).mode;
editor.session.setMode(mode);
  
}

//add the editor to the DOM
//Str is filename 
function addEditor(str) {
  $('#editor-container').show();
  $('#container').css("background-color", "none");
  $('#std-out').hide();
  $('#std-in').hide();
  setupEditor(str); 
}

function closeEditor() {
  $('#editor-container').hide();
  $('#container').css('background-color', term_bg_color);
  $('#std-out').show();
  $('#std-in').show();
  $('#theme_tab').hide();
}

function socket_init() {
var userName; 
var socket = io();
//Login
$('#login').on("click", function(){
  var username = $('#username').val();
  userName = username;
  var hostname = $('#host').val();
  var password = $('#password').val();
  $('#machine_login_modal').remove();
  socket.emit('login', {user: username, pass: password, host: hostname});
  return false;
});

//LS area 
$('#LS').on("click", function(){
  socket.emit('getFileList');
  return false;
});
socket.on('FileList', function(list){
  $('#dump').append(list);
  $.event.trigger({
    type: "generateLS"
  });
  
})
//If file setup and show the editor
socket.on('file',function(dic){
  var editor = ace.edit("editor");
  editor.setValue(dic.data_in);
  addEditor(dic.name);
  dicToSend = dic;

});



//Enter Command 
$('#stdinF').submit(function(){
  socket.emit('cmd', $('#std-in').val());
  $('#std-in').val('');
  return false;
});

//Parsing the output to #std-out
socket.on('output', function(output){
  output = output.replace('\r\r\n',"<br>");
  console.log(output);
  var endLine = userName+'[';
  console.log(userName);
  var index = output.indexOf(endLine);
  console.log(index);
  var substring = output.substring(0,index);
  var substring2 = output.substring(index, output.length);
  console.log(substring);
  console.log("hi");
  $('#std-out').append(substring + "<br>");
  $('#std-out').append(substring2);
  $('#std-out').animate({
        scrollTop: $('#std-out')[0].scrollHeight}, 100);

});


}