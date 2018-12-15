<table>
    <tr>
        <td><label>Choose video type</label></td>
        <td colspan="5">
            <select class="form-select layer-option" name="video_type" onchange="video_type_change(this.value)">
                <option value="youtube">YouTube</option>
                <option value="vimeo">Vimeo</option>
                <option value="html5">HTML5</option>
            </select>
        </td>
    </tr>
    <tr>
        <td><label>Video Ratio</label></td>
        <td>
            <select class="form-select layer-option" name="aspectratio">
                <option value="16:9">16:9</option>
                <option value="4:3">4:3</option>
            </select>
        </td>
        <td>
            <label>Autoplay only first time</label>
        </td>
        <td>
            <select class="form-select layer-option" name="autoplayonlyfirsttime">
                <option value="true">Yes</option>
                <option value="false">No</option>
            </select>
            <div class="description">After first Autplay the video will not be played automatically</div>
        </td>
        <td>
            <label>Force rewind</label>
        </td>
        <td>
            <select class="form-select layer-option" name="forcerewind">
                <option value="on">On</option>
                <option value="off">Off</option>
            </select>
            <div class="description">Every time the Slide is shown, the Video will rewind to the start.</div>
        </td>
    </tr>
    <tr id="youtube_video">
        <td><label>Enter Youtube ID</label></td>
        <td colspan="5"><input class="layer-option form-text" name="youtube_video"/></td>
    </tr>
    <tr id="vimeo_video">
        <td><label>Enter Vimeo ID</label></td>
        <td colspan="5"><input class="layer-option form-text" name="vimeo_video"/></td>
    </tr>
    <tbody id="html5_video">
    <tr>
        <td><label>Poster Image</label></td>
        <td colspan="5">
            <input id="imagelayer" class="layer-option file-imce form-text" data-uri="[name=html5_video_poster_uri]" name="html5_video_poster">
            <input name="html5_video_poster_uri" type="hidden" class="layer-option"/>
        </td>
    </tr>
    <tr>
        <td><label>Video MP4</label></td>
        <td>
            <input id="imagelayer" class="layer-option form-text" name="html5_video_mp4">
        </td>
        <td><label>Video WEBM</label></td>
        <td>
            <input id="imagelayer" class="layer-option form-text" name="html5_video_webm">
        </td>
        <td><label>Video OGV</label></td>
        <td>
            <input id="imagelayer" class="layer-option form-text" name="html5_video_ogv">
        </td>
    </tr>
    </tbody>
    <tr>
        <td>
            <label>Full Width</label>
        </td>
        <td>
            <select class="layer-option form-select" onchange="video_fullwidth_change(this.value)" name="video_fullwidth">
                <option value="1">Yes</option>
                <option value="0">No</option>
            </select>
        </td>
        <td class="un-fullwidth">
            <label>Width</label>
        </td>
        <td class="un-fullwidth">
            <input name="video_width" class="form-text layer-option"/>
        </td>
        <td class="un-fullwidth">
            <label>Height</label>
        </td>
        <td class="un-fullwidth">
            <input name="video_height" class="form-text layer-option"/>
        </td>
    </tr>
    <tr>
        <td><label>Autoplay</label></td>
        <td>
            <select name="video_autoplay" class="form-select layer-option">
            <option value="0">No</option>
            <option value="1">Yes</option>
          </select>
        </td>
        <td><label>Mute</label></td>
        <td>
            <select name="video_mute" class="form-select layer-option">
                <option value="1">Yes</option>
                <option value="0">No</option>
            </select>
        </td>
        <td><label>Loop</label></td>
        <td>
            <select name="video_loop" class="form-select layer-option">
                <option value="none">None</option>
                <option value="loop">Loop</option>
                <option value="loopandnoslidestop">Loop and no slide stop</option>
            </select>
        </td>
    </tr>
    <tr>
        <td><label>Controls</label></td>
        <td>
            <select name="video_controls" class="form-select layer-option">
                <option value="1">Yes</option>
                <option value="0">No</option>
            </select>
        </td>
        <td><label>Next Slide at End</label></td>
        <td colspan="1">
            <select name="video_nextslideatend" class="form-select layer-option">
                <option value="1">Yes</option>
                <option value="0">No</option>
            </select>
        </td>
        <td colspan="2">
            <label>Dotted Overlay</label>
            <select name="video_dottedoverlay" class="form-select layer-option">
                <option value="none">none</option>
                <option value="twoxtwo">twoxtwo</option>
                <option value="threexthree">threexthree</option>
                <option value="twoxtwowhite">twoxtwowhite</option>
                <option value="threexthreewhite">threexthreewhite</option>
            </select>
        </td>
    </tr>
</table>
<script type="text/javascript">
    function video_type_change(video_type){
        var visible_tab_id = '#'+ video_type+'_video';
        jQuery('#youtube_video,#vimeo_video,#html5_video').hide();
        jQuery(visible_tab_id).show();
    }
    function video_fullwidth_change(val){
        if(parseInt(val)===1){
            jQuery('td.un-fullwidth').css('visibility','hidden');
        }else{
            jQuery('td.un-fullwidth').css('visibility','visible');
        }
    }
</script>
