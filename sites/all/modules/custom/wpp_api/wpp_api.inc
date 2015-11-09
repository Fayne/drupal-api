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
 * Callback function for company retrieve
 *
 * @param $companyCode
 * @return mixed
 */
function _wpp_api_company_retrieve($companyCode) {

    return _wpp_api_output_company($companyCode);

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
    $galleryAPI->titleEN = $gallery->title;
    $galleryAPI->titleCN = isset($gallery->field_title_chinese[LANGUAGE_NONE][0]['value']) ? $gallery->field_title_chinese[LANGUAGE_NONE][0]['value'] : '';

    $galleryAPI->subTitleEN = isset($gallery->field_subtitle[LANGUAGE_NONE][0]['value']) ? $gallery->field_subtitle[LANGUAGE_NONE][0]['value'] : '';
    $galleryAPI->subTitleCN = isset($gallery->field_subtitle_chinese[LANGUAGE_NONE][0]['value']) ? $gallery->field_subtitle_chinese[LANGUAGE_NONE][0]['value'] : '';

    $galleryAPI->descriptionEN = isset($gallery->body[LANGUAGE_NONE][0]['value']) ? $gallery->body[LANGUAGE_NONE][0]['value'] : '';
    $galleryAPI->descriptionCN = $gallery->field_description_chinese[LANGUAGE_NONE][0]['value'] ?: '';
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
        $galleryAPI->titleEN = $gallery->title;
        $galleryAPI->titleCN = isset($gallery->field_title_chinese[LANGUAGE_NONE][0]['value']) ? $gallery->field_title_chinese[LANGUAGE_NONE][0]['value'] : '';
        $galleryAPI->subTitleEN = isset($gallery->field_subtitle[LANGUAGE_NONE][0]['value']) ? $gallery->field_subtitle[LANGUAGE_NONE][0]['value'] : '';
        $galleryAPI->subTitleCN = isset($gallery->field_subtitle_chinese[LANGUAGE_NONE][0]['value']) ? $gallery->field_subtitle_chinese[LANGUAGE_NONE][0]['value'] : '';

        if ($detail === 'true') {
            $galleryAPI->descriptionEN = isset($gallery->body[LANGUAGE_NONE][0]['value']) ? $gallery->body[LANGUAGE_NONE][0]['value'] : '';
            $galleryAPI->descriptionCN = $gallery->field_description_chinese[LANGUAGE_NONE][0]['value'] ?: '';
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
        if (isset($floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri']);
        }
        if (isset($floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri']);
        }
        if (isset($floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri']);
        }

        $floorAPI->sliders = $sliders;

        $logoReferences = $floor->field_floor_logo_reference[LANGUAGE_NONE];
        $logos = array();
        foreach ($logoReferences as $index => $logoReference) {
            $logoId = $logoReference['target_id'];
            $logo = node_load($logoId);

            $logos[] = [
                "url" => file_create_url($logo->field_floor_logo[LANGUAGE_NONE][0]['uri']), 
                "order" => $index + 1
            ];
        }

        $floorAPI->logos = $logos;
    }

    return $floorAPI;
}

/**
 * Get company detail by given company code.
 *
 * @param string $companyCode
 *
 * @return stdClass
 */
function _wpp_api_output_company($companyCode = '') {

    $companyAPI = new stdClass();

    $query = new EntityFieldQuery();
    $query
        ->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'company')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldCondition('field_company_code', 'value', $companyCode)
        ->range(0, 1);

    $result = $query->execute();

    if (isset($result['node'])) {

        $companyNid = current(array_keys($result['node']));
        $company = node_load($companyNid);

        $companyAPI->titleEN = $company->title;
        $companyAPI->titleCN = $company->field_company_title_cn[LANGUAGE_NONE][0]['value'];
        $companyAPI->floorNumber = $company->field_company_floor_number[LANGUAGE_NONE][0]['value'];
        $companyAPI->companycode = $company->field_company_code[LANGUAGE_NONE][0]['value'];
        $companyAPI->introductionEN = $company->field_company_intro_english[LANGUAGE_NONE][0]['value'];
        $companyAPI->introductionCN = $company->field_company_intro_chinese[LANGUAGE_NONE][0]['value'];
        $companyAPI->contactNumber = $company->field_company_contact_number[LANGUAGE_NONE][0]['value'];
        $companyAPI->addressEN = $company->field_company_address_english[LANGUAGE_NONE][0]['value'];
        $companyAPI->addressCN = $company->field_company_address_chinese[LANGUAGE_NONE][0]['value'];

        $sliders = array();
        if (isset($company->field_company_slider_image_1[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($company->field_company_slider_image_1[LANGUAGE_NONE][0]['uri']);
        }
        if (isset($company->field_company_slider_image_2[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($company->field_company_slider_image_2[LANGUAGE_NONE][0]['uri']);
        }
        if (isset($company->field_company_slider_image_3[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($company->field_company_slider_image_3[LANGUAGE_NONE][0]['uri']);
        }

        $companyAPI->sliders = $sliders;
    }

    return $companyAPI;
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
        if (isset($floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_1[LANGUAGE_NONE][0]['uri']);
        }
        if (isset($floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_2[LANGUAGE_NONE][0]['uri']);
        }
        if (isset($floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri'])) {
            $sliders[] = file_create_url($floor->field_floor_slider_image_3[LANGUAGE_NONE][0]['uri']);
        }

        // $floorAPI->sliders = $sliders;

        $logoReferences = $floor->field_floor_logo_reference[LANGUAGE_NONE];
        $logos = array();
        foreach ($logoReferences as $index => $logoReference) {
            $logoId = $logoReference['target_id'];
            $logo = node_load($logoId);

            $logos[] = [
                "url" => file_create_url($logo->field_floor_logo[LANGUAGE_NONE][0]['uri']), 
                "order" => $index + 1
            ];
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
    $dealAPI->shopNameEN = $deal->title;
    $dealAPI->shopNameCN = isset($deal->field_title_chinese[LANGUAGE_NONE][0]['value']) ? $deal->field_title_chinese[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->shopDescriptionEN = isset($deal->field_shop_description_english[LANGUAGE_NONE][0]['value']) ? $deal->field_shop_description_english[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->shopDescriptionCN = isset($deal->field_shop_description_chinese[LANGUAGE_NONE][0]['value']) ? $deal->field_shop_description_chinese[LANGUAGE_NONE][0]['value'] : '';

    if ($deal->field_latitude && $deal->field_longitude) {
        $dealAPI->coordinates = (object) [
            "latitude" => $deal->field_latitude[LANGUAGE_NONE][0]['value'], 
            "longitude" => $deal->field_longitude[LANGUAGE_NONE][0]['value']
        ];
    } else {
        $dealAPI->coordinates = (object) ["latitude" => "", "longitude" => ""];
    }
    $dealAPI->addressEN = isset($deal->field_address[LANGUAGE_NONE][0]['value']) ? $deal->field_address[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->addressCN = isset($deal->field_address_chinese[LANGUAGE_NONE][0]['value']) ? $deal->field_address_chinese[LANGUAGE_NONE][0]['value'] : '';
    
    $dealAPI->categoriesEN = isset($deal->field_category[LANGUAGE_NONE]) ? _array_flatten($deal->field_category[LANGUAGE_NONE]) : [];
    $dealAPI->categoriesCN = isset($deal->field_category_chinese[LANGUAGE_NONE]) ? _array_flatten($deal->field_category_chinese[LANGUAGE_NONE]) : [];
    $dealAPI->averageSpendEN = isset($deal->field_average_spend[LANGUAGE_NONE][0]['value']) ? $deal->field_average_spend[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->averageSpendCN = isset($deal->field_average_spend_chinese[LANGUAGE_NONE][0]['value']) ? $deal->field_average_spend_chinese[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->hasDeal = isset($deal->field_has_deal[LANGUAGE_NONE][0]['value']) ? (int) $deal->field_has_deal[LANGUAGE_NONE][0]['value'] : 0;
    $dealAPI->detailsEN = isset($deal->field_details[LANGUAGE_NONE][0]['value']) ? $deal->field_details[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->detailsCN = isset($deal->field_details_chinese[LANGUAGE_NONE][0]['value']) ? $deal->field_details_chinese[LANGUAGE_NONE][0]['value'] : '';

    $shopPictures = array();
    if ($deal->field_shop_pictures_1 && $deal->field_shop_pictures_1[LANGUAGE_NONE][0]['uri']) {
        $shopPictures[] = file_create_url($deal->field_shop_pictures_1[LANGUAGE_NONE][0]['uri']);
    }
    if ($deal->field_shop_pictures_2 && $deal->field_shop_pictures_2[LANGUAGE_NONE][0]['uri']) {
        $shopPictures[] = file_create_url($deal->field_shop_pictures_2[LANGUAGE_NONE][0]['uri']);
    }
    if ($deal->field_shop_pictures_3 && $deal->field_shop_pictures_3[LANGUAGE_NONE][0]['uri']) {
        $shopPictures[] = file_create_url($deal->field_shop_pictures_3[LANGUAGE_NONE][0]['uri']);
    }

    $dealAPI->shopPictures = $shopPictures;
    $dealAPI->shopTagEN = isset($deal->field_shop_tag[LANGUAGE_NONE][0]['value']) ? $deal->field_shop_tag[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->shopTagCN = isset($deal->field_shop_tag_chinese[LANGUAGE_NONE][0]['value']) ? $deal->field_shop_tag_chinese[LANGUAGE_NONE][0]['value'] : '';
    $dealAPI->telephone = isset($deal->field_telephone[LANGUAGE_NONE][0]['value']) ? $deal->field_telephone[LANGUAGE_NONE][0]['value'] : '';

    return $dealAPI;
}

function _wpp_api_output_deal_list($dealList = array()) {
    $dealListAPI = array();

    foreach($dealList as $deal) {
        array_push($dealListAPI, _wpp_api_output_deal($deal));
    }

    return $dealListAPI;
}

/**
 * Notify WPP when a user leaves a feedback.
 *
 * @param $email the user email address
 * @param $name the user full name
 * @param $message the user message
 *
 * @return mixed
 */
function _wpp_api_user_feedback($email, $name, $message) {
    $params['email'] = $email;
    $params['name'] = $name;
    $params['message'] = $message;

    $mail = drupal_mail('wpp_api', 'user_feedback', variable_get('wpp_api_feedback_email', 'djamel@mobilenowgroup.com'), language_default(), $params);

    if (!empty($mail)) {
        return array(
            'succcess' => true, 
            'message' => t('User feedback has been sent successfully.'),
        );
    }

    return array(
        'succcess' => false, 
        'message' => t('Sorry, there was a problem when sending the email. Please try again.'),
    );
}

/**
 * Implements hook_mail().
 */
function wpp_api_mail($key, &$message, $params) {

    switch ($key) {
        case 'user_feedback':
            $subject = t('WPP Campus | User Feedback');
            $body = t("Dear Admin,

A feedback has been sent from WPP Campus APP.

---
Name: [app-user:name]

Email: [app-user:email]

Message:
[app-user:message]
---

--  WPP Campus CMS");
            break;    
    }

    $message['subject'] = $subject;
    $message['body'][] = token_replace($body, $params, array('language' => language_default(), 'callback' => 'wpp_api_mail_tokens', 'sanitize' => FALSE, 'clear' => TRUE));
}

/**
 * Token callback to add unsafe tokens for user mails.
 *
 * This function is used by the token_replace() call 
 * to set up some additional tokens that can be
 * used in email messages generated by wpp_api_mail().
 *
 * @param $replacements
 * @param $data
 * @param $options
 */
function wpp_api_mail_tokens(&$replacements, $data, $options) {
    $replacements['[app-user:name]'] = $data['name'];
    $replacements['[app-user:email]'] = $data['email'];
    $replacements['[app-user:message]'] = $data['message'];
}

function _array_flatten($array) {
    $return = array();

    array_walk_recursive($array, function ($x) use (&$return) {
        $return[] = $x;
    });

    return $return;
}