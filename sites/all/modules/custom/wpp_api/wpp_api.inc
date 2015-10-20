<?php

/**
 * Determine whether the current user can access a node resource.
 *
 * @param $op
 *   One of view, update, create, delete per node_access().
 * @param $args
 *   Resource arguments passed through from the original request.
 * @return bool
 *
 * @see node_access()
 */
function _wpp_api_node_resource_access($op = 'view', $args = array()) {
    return TRUE;
}

/**
 * Callback function for gallery retrieve
 * @param null $nid
 * @return array
 */
function _wpp_api_gallery_retrieve($nid = NULL) {

    $gallery = node_load($nid);

    return _wpp_api_output_gallery($gallery);

}

/**
 * Callback function for deal retrieve
 * @param null $nid
 * @return array
 */
function _wpp_api_deal_retrieve($nid = NULL) {

    $deal = node_load($nid);

    return _wpp_api_output_deal($deal);

}

/**
 * Callback function for gallery list
 *
 * @param $offset
 * @param $limit
 * @param string $detail 'true' | 'false'
 * @return array
 */
function _wpp_api_gallery_list($offset, $limit, $detail) {
    $galleryList = node_load_multiple(array(), array('type' => 'article'));

    $galleryList = $limit ? array_slice($galleryList, $offset, $limit) : array_slice($galleryList, $offset);

    return _wpp_api_output_gallery_list($galleryList, $detail);
}

/**
 * Callback function for beacon list
 *
 * @return mixed
 */
function _wpp_api_beacon_list() {
    $beaconList = node_load_multiple(array(), array('type' => 'beacon'));

    return _wpp_api_output_beacon_list($beaconList);
}

/**
 * Callback function for floor list
 *
 * @param $offset
 * @param $limit
 * @return array
 */
function _wpp_api_floor_list($offset, $limit) {
    $floorList = node_load_multiple(array(), array('type' => 'floor'));

    $floorList = $limit ? array_slice($floorList, $offset, $limit) : array_slice($floorList, $offset);

    return _wpp_api_output_floor_list($floorList);
}

/**
 * Callback function for deal list
 *
 * @param $offset
 * @param $limit
 * @return array
 */
function _wpp_api_deal_list($offset, $limit) {

    $query = new EntityFieldQuery();
    $query
        ->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'deal')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->propertyOrderBy('changed', 'DESC');

    $entities = $query->execute();

    $dealList = node_load_multiple(array_keys($entities['node']));

    $dealList = $limit ? array_slice($dealList, $offset, $limit) : array_slice($dealList, $offset);

    return _wpp_api_output_deal_list($dealList);
}

/**
 * Get gallery post
 * @param object $gallery
 * @return array
 */
function _wpp_api_output_gallery($gallery) {
    $galleryAPI = new stdClass();

    $galleryAPI->id = (int) $gallery->nid;
    $galleryAPI->title = $gallery->title;
    $galleryAPI->subTitle = isset($gallery->field_subtitle[LANGUAGE_NONE][0]['value']) ? $gallery->field_subtitle[LANGUAGE_NONE][0]['value'] : '';
    $galleryAPI->description = isset($gallery->body[LANGUAGE_NONE][0]['value']) ? $gallery->body[LANGUAGE_NONE][0]['value'] : '';
    $galleryAPI->type = isset($gallery->field_type[LANGUAGE_NONE][0]['tid']) ? _get_term_name_by_id($gallery->field_type[LANGUAGE_NONE][0]['tid']) : '';
    $galleryAPI->thumbnail = isset($gallery->field_image[LANGUAGE_NONE][0]['uri']) ? file_create_url($gallery->field_image[LANGUAGE_NONE][0]['uri']) : '';
    $galleryAPI->cover = isset($gallery->field_cover[LANGUAGE_NONE][0]['uri']) ? file_create_url($gallery->field_cover[LANGUAGE_NONE][0]['uri']) : '';

    if ($video = isset($gallery->field_video[LANGUAGE_NONE][0]['uri']) ? file_create_url($gallery->field_video[LANGUAGE_NONE][0]['uri']) : '') {
        $galleryAPI->video = $video;
    }

    $galleryAPI->publishedAt = isset($gallery->field_published[LANGUAGE_NONE][0]['value']) ? $gallery->field_published[LANGUAGE_NONE][0]['value'] : '';
    $galleryAPI->updateAt = date(DATE_ISO8601, $gallery->changed);

    return $galleryAPI;
}

/**
 * Get gallery posts
 * @param array $galleryList
 * @param string $detail
 * @return array
 */
function _wpp_api_output_gallery_list($galleryList = array(), $detail = 'false') {
    $galleryListAPI = array();

    foreach ($galleryList as $gallery) {
        $galleryAPI = new stdClass();

        $galleryAPI->id = (int) $gallery->nid;
        $galleryAPI->title = $gallery->title;
        $galleryAPI->subTitle = isset($gallery->field_subtitle[LANGUAGE_NONE][0]['value']) ? $gallery->field_subtitle[LANGUAGE_NONE][0]['value'] : '';

        if ($detail === 'true') {
            $galleryAPI->description = isset($gallery->body[LANGUAGE_NONE][0]['value']) ? $gallery->body[LANGUAGE_NONE][0]['value'] : '';
        }

        $galleryAPI->type = isset($gallery->field_type[LANGUAGE_NONE][0]['tid']) ? _get_term_name_by_id($gallery->field_type[LANGUAGE_NONE][0]['tid']) : '';
        $galleryAPI->thumbnail = isset($gallery->field_image[LANGUAGE_NONE][0]['uri']) ? file_create_url($gallery->field_image[LANGUAGE_NONE][0]['uri']) : '';
        $galleryAPI->cover = isset($gallery->field_cover[LANGUAGE_NONE][0]['uri']) ? file_create_url($gallery->field_cover[LANGUAGE_NONE][0]['uri']) : '';

        if ($video = isset($gallery->field_video[LANGUAGE_NONE][0]['uri']) ? file_create_url($gallery->field_video[LANGUAGE_NONE][0]['uri']) : '') {
            $galleryAPI->video = $video;
        }

        $galleryAPI->publishedAt = isset($gallery->field_published[LANGUAGE_NONE][0]['value']) ? $gallery->field_published[LANGUAGE_NONE][0]['value'] : '';
        $galleryAPI->updateAt = date(DATE_ISO8601, $gallery->changed);

        array_push($galleryListAPI, $galleryAPI);
    }

    return $galleryListAPI;
}

/**
 * Get beacon list
 *
 * @param array $beaconList
 * @return array
 */
function _wpp_api_output_beacon_list($beaconList = array()) {
    $beaconListAPI = array();

    foreach ($beaconList as $beacon) {
        $beaconAPI = new stdClass();

        $beaconAPI->uuid = $beacon->field_uuid[LANGUAGE_NONE][0]['value'];
        $beaconAPI->name = $beacon->title;
        $beaconAPI->major = (int) $beacon->field_major[LANGUAGE_NONE][0]['value'];
        $beaconAPI->minor = (int) $beacon->field_minor[LANGUAGE_NONE][0]['value'];
        $beaconAPI->distance = isset($beacon->field_distance[LANGUAGE_NONE][0]['value']) ? (int) $beacon->field_distance[LANGUAGE_NONE][0]['value'] : '';

        // check whether it has reference content
        if ($contentId = isset($beacon->field_beacon_content[LANGUAGE_NONE][0]['target_id']) ? $beacon->field_beacon_content[LANGUAGE_NONE][0]['target_id'] : '') {
            global $base_url;

            // get the current endpoint path
            $endpoints = services_endpoint_load_all();
            $currentPath = '';

            foreach ($endpoints as $endpoint) {
                if (strpos(current_path(), $endpoint->path) === 0) {
                    $currentPath = $endpoint->path;

                    break;
                }
            }

//            $content = node_load($contentId);

            $beaconAPI->content = array(
                'id' => (int) $contentId,
                'type' => WPP_API_GALLERY_TYPE,
                'href' => $currentPath ? $base_url . '/' . $currentPath . '/' . WPP_API_GALLERY_TYPE . '/' . $contentId : "",
            );
        }

        $beaconAPI->updateAt = date(DATE_ISO8601, $beacon->changed);

        array_push($beaconListAPI, $beaconAPI);
    }

    return $beaconListAPI;
}

/**
 * Get term name by given tid.
 *
 * @param int $tid
 * @return string mixed
 */
function _get_term_name_by_id($tid) {
    $taxonomyTerm = taxonomy_term_load($tid);

    return $taxonomyTerm->name;
}

/**
 * Get floor detail by given $floorNumber.
 *
 * @param $floorNumber
 * @return mixed
 */
function _wpp_api_floor_retrieve($floorNumber) {
    $floorAPI = new stdClass();

    $query = new EntityFieldQuery();
    $query
        ->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'floor')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldCondition('field_floor_number', 'value', $floorNumber)
        ->range(0, 1);

    $result = $query->execute();

    if (isset($result['node'])) {

        $floorNid = current(array_keys($result['node']));
        $floor = node_load($floorNid);

        $floorAPI->title = $floor->title;
        $floorAPI->floorNumber = $floor->field_floor_number[LANGUAGE_NONE][0]['value'];
        $floorAPI->color = $floor->field_floor_color[LANGUAGE_NONE][0]['value'];
        $floorAPI->introductionEN = $floor->field_floor_introduction_english[LANGUAGE_NONE][0]['value'];
        $floorAPI->introductionCN = $floor->field_floor_introduction_chinese[LANGUAGE_NONE][0]['value'];
        $floorAPI->contactNumber = $floor->field_floor_contact_number[LANGUAGE_NONE][0]['value'];
        $floorAPI->addressEN = $floor->field_floor_address_english[LANGUAGE_NONE][0]['value'];
        $floorAPI->addressCN = $floor->field_floor_address_chinese[LANGUAGE_NONE][0]['value'];

        $sliders = array();
        if ($floor->field_floor_slider_image_1 && $floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri']) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri']);
        }
        if ($floor->field_floor_slider_image_2 && $floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri']) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri']);
        }
        if ($floor->field_floor_slider_image_3 && $floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri']) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri']);
        }

        $floorAPI->sliders = $sliders;

        $logoReferences = $floor->field_floor_logo_reference[LANGUAGE_NONE];
        $logos = array();
        foreach ($logoReferences as $logoReference) {
            $logoId = $logoReference['target_id'];
            $logo = node_load($logoId);

            $logos[] = file_create_url($logo->field_floor_logo[LANGUAGE_NONE][0]['uri']);
        }

        $floorAPI->logos = $logos;
    }

    return $floorAPI;
}

/**
 * Get floor list
 *
 * @param array $floorList
 * @return array
 */
function _wpp_api_output_floor_list ($floorList = array()) {
    $floorListAPI = array();

    foreach ($floorList as $floor) {
        $floorAPI = new stdClass();

        $floorAPI->title = $floor->title;
        $floorAPI->floorNumber = $floor->field_floor_number[LANGUAGE_NONE][0]['value'];
        $floorAPI->color = $floor->field_floor_color[LANGUAGE_NONE][0]['value'];
        // $floorAPI->introductionEN = $floor->field_floor_introduction_english[LANGUAGE_NONE][0]['value'];
        // $floorAPI->introductionCN = $floor->field_floor_introduction_chinese[LANGUAGE_NONE][0]['value'];
        // $floorAPI->contactNumber = $floor->field_floor_contact_number[LANGUAGE_NONE][0]['value'];
        // $floorAPI->addressEN = $floor->field_floor_address_english[LANGUAGE_NONE][0]['value'];
        // $floorAPI->addressCN = $floor->field_floor_address_chinese[LANGUAGE_NONE][0]['value'];

        $sliders = array();
        if ($floor->field_floor_slider_image_1 && $floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri']) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri']);
        }
        if ($floor->field_floor_slider_image_2 && $floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri']) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri']);
        }
        if ($floor->field_floor_slider_image_3 && $floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri']) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri']);
        }

        // $floorAPI->sliders = $sliders;

        $logoReferences = $floor->field_floor_logo_reference[LANGUAGE_NONE];
        $logos = array();
        foreach ($logoReferences as $logoReference) {
            $logoId = $logoReference['target_id'];
            $logo = node_load($logoId);

            $logos[] = file_create_url($logo->field_floor_logo[LANGUAGE_NONE][0]['uri']);
        }

        $floorAPI->logos = $logos;

        array_push($floorListAPI, $floorAPI);
    }

    return $floorListAPI;
}

/**
 * Get deal detail by given $dealId.
 *
 * @param $deal
 * @return mixed
 */
function _wpp_api_output_deal($deal) {
    $dealAPI = new stdClass();

    $dealAPI->id = (int) $deal->nid;
    $dealAPI->shopName = $deal->title;
    $dealAPI->shopDescriptionEN = isset($deal->field_shop_description_english[LANGUAGE_NONE][0]['value']) ? $deal->field_shop_description_english[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->shopDescriptionCN = isset($deal->field_shop_description_chinese[LANGUAGE_NONE][0]['value']) ? $deal->field_shop_description_chinese[LANGUAGE_NONE][0]['value'] : '';

    if ($deal->field_latitude && $deal->field_longtitude) {
        $dealAPI->coordinates = (object) [
            "latitude" => $deal->field_latitude[LANGUAGE_NONE][0]['value'], 
            "longtitude" => $deal->field_longtitude[LANGUAGE_NONE][0]['value']
        ];
    } else {
        $dealAPI->coordinates = (object) ["latitude" => "", "longtitude" => ""];
    }
    
    $dealAPI->categories = isset($deal->field_category[LANGUAGE_NONE]) ? $deal->field_category[LANGUAGE_NONE] : [];
    $dealAPI->averageSpend = isset($deal->field_average_spend[LANGUAGE_NONE][0]['value']) ? $deal->field_average_spend[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->hasDeal = (int) $deal->field_has_deal[LANGUAGE_NONE][0]['value'];
    $dealAPI->details = isset($deal->field_details[LANGUAGE_NONE][0]['value']) ? $deal->field_details[LANGUAGE_NONE][0]['value'] : '';

    $shopPictures = array();
    if ($deal->field_shop_pictures_1 && $floor->field_shop_pictures_1[LANGUAGE_NONE][0]['uri']) {
        $shopPictures[] = file_create_url($floor->field_shop_pictures_1[LANGUAGE_NONE][0]['uri']);
    }
    if ($deal->field_shop_pictures_2 && $floor->field_shop_pictures_2[LANGUAGE_NONE][0]['uri']) {
        $shopPictures[] = file_create_url($floor->field_shop_pictures_2[LANGUAGE_NONE][0]['uri']);
    }
    if ($deal->field_shop_pictures_3 && $floor->field_shop_pictures_3[LANGUAGE_NONE][0]['uri']) {
        $shopPictures[] = file_create_url($floor->field_shop_pictures_3[LANGUAGE_NONE][0]['uri']);
    }

    $dealAPI->shopPictures = $shopPictures;
    $dealAPI->shopTag = isset($deal->field_shop_tag[LANGUAGE_NONE][0]['value']) ? $deal->field_shop_tag[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->telephone = isset($deal->field_telephone[LANGUAGE_NONE][0]['value']) ? $deal->field_telephone[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->address = isset($deal->field_address[LANGUAGE_NONE][0]['value']) ? $deal->field_address[LANGUAGE_NONE][0]['value'] : '';

    return $dealAPI;
}

function _wpp_api_output_deal_list($dealList = array()) {
    $dealListAPI = array();

    foreach($dealList as $deal) {
        array_push($dealListAPI, _wpp_api_output_deal($deal));
    }

    return $dealListAPI;
}