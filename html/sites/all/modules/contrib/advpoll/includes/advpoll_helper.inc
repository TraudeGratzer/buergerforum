<?php

/*
 * @file
 * Advanced Poll Helper Include
 * 
 * Helper functions for converting node and form data into a more readable
 * and compact format that can easily be passed to sub-functions and templates.
 */

/**
 * Returns an object with a predictable structure regardless of content type.
 * It basically saves having to extract the data in any given function that 
 * retrieves specific fields from a node.
 *
 * @param $node - a node generated by any of the advanced poll modules.
 * @return
 *   object containing the following fields.
 *   choices:
 *      array containing:
 *        choice_id = the unique hex id of the choice
 *        choice =    The text for a given choice.
 *        write_in =  a boolean value indicating whether or not the choice was a 
 *                    write in.
 *   start_date:      (int) Start date of the poll
 *   end_date:        (int) End date of the poll
 *   mode:            The mode used to store the vote: normal, cookie, unlimited
 *   cookie_duration: (int) If mode is cookie, the number of minutes to delay votes.
 *   state:           Is the poll 'open' or 'close'
 *   behavior:        approval or pool - determines how to treat multiple vote/user 
 *                    tally. When plugin is installed, voting will default to tabulating
 *                    values returned from voting API.
 *   max_choices:     (int) How many choices a user can select per vote.
 *   show_results:    When to display results - aftervote, afterclose or never.
 *   electoral:       Boolean - voting restricted to users in an electoral list.
 *   write_in:        Boolean - all write-in voting.
 *   block:           Boolean - Poll can be displayed as a block.
 */
function advpoll_get_data($node) {
  $data = array();
  $lang = $node->language;
  $options = array();

  if ($node->type == 'advpoll') {
    // testing each field to make sure there is no translated version
    if ($node->advpoll_options) {
      (isset($node->advpoll_options[$lang])) ? $options = $node->advpoll_options[$lang] : $options = $node->advpoll_options['und'];
    }
    (isset($node->advpoll_choice[$lang])) ? $data['choices'] = $node->advpoll_choice[$lang] : $data['choices'] = $node->advpoll_choice['und'];

    if ($node->advpoll_dates) {
      (isset($node->advpoll_dates[$lang])) ? $data['start_date'] = strtotime($node->advpoll_dates[$lang][0]['value']) : $data['start_date'] = strtotime($node->advpoll_dates['und'][0]['value']);
      (isset($node->advpoll_dates[$lang])) ? $data['end_date'] = strtotime($node->advpoll_dates[$lang][0]['value2']) : $data['end_date'] = strtotime($node->advpoll_dates['und'][0]['value2']);
    } else {
      $data['start_date'] = 0;
      $data['end_date'] = 0;
    }

    (isset($node->advpoll_mode[$lang])) ? $data['mode'] = $node->advpoll_mode[$lang][0]['value'] : $data['mode'] = $node->advpoll_mode['und'][0]['value'];
    (isset($node->advpoll_cookie_duration[$lang])) ? $data['cookie_duration'] = $node->advpoll_cookie_duration[$lang][0]['value'] : $data['cookie_duration'] = $node->advpoll_cookie_duration['und'][0]['value'];
    (isset($node->advpoll_closed[$lang])) ? $data['state'] = $node->advpoll_closed[$lang][0]['value'] : $data['state'] = $node->advpoll_closed['und'][0]['value'];
    (isset($node->advpoll_behavior[$lang])) ? $data['behavior'] = $node->advpoll_behavior[$lang][0]['value'] : $data['behavior'] = $node->advpoll_behavior['und'][0]['value'];
    (isset($node->advpoll_max_choices[$lang])) ? $data['max_choices'] = $node->advpoll_max_choices[$lang][0]['value'] : $data['max_choices'] = $node->advpoll_max_choices['und'][0]['value'];
    (isset($node->advpoll_results[$lang])) ? $data['show_results'] = $node->advpoll_results[$lang][0]['value'] : $data['show_results'] = $node->advpoll_results['und'][0]['value'];
    $data['electoral'] = advpoll_has_data($options, 'electoral');
    $data['write_in'] = advpoll_has_data($options, 'writein');
    $data['block'] = advpoll_has_data($options, 'block');
  }

  return (object) $data;
}

// convenience function to find value in a nested array.
function advpoll_has_data($options, $term) {

  foreach ($options as $option) {
    if ($option['value'] == $term) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Returns an object with a predictable structure regardless of content type form state.
 * This call returns the same data structure as the advpoll_get_data() call, only
 * using form_state data rather than node data.
 *
 * @param $form_state - form_state returned from a node submission.
 * @return
 *   object containing the following fields.
 *   choices:
 *      array containing:
 *        choice_id = the unique hex id of the choice
 *        choice =    The text for a given choice.
 *        write_in =  a boolean value indicating whether or not the choice was a 
 *                    write in.
 *   start_date:      (int) Start date of the poll
 *   end_date:        (int) End date of the poll
 *   mode:            The mode used to store the vote: normal, cookie, unlimited
 *   cookie_duration: (int) If mode is cookie, the number of minutes to delay votes.
 *   state:           Is the poll 'open' or 'close'
 *   behavior:        approval or pool - determines how to treat multiple vote/user 
 *                    tally. When plugin is installed, voting will default to tabulating
 *                    values returned from voting API.
 *   max_choices:     (int) How many choices a user can select per vote.
 *   show_results:    When to display results - aftervote, afterclose or never.
 *   electoral:       Boolean - voting restricted to users in an electoral list.
 *   write_in:        Boolean - all write-in voting.
 *   block:           Boolean - Poll can be displayed as a block.
 */
function advpoll_get_form_data($form_state, $index=0) {
  $data = array();
  $node = $form_state['build_info']['args'][$index];
  $lang = $node->language;
  $options = array();

  if ($node->type == 'advpoll') {
    if ($node->advpoll_options) {
      (isset($node->advpoll_options[$lang])) ? $options = $node->advpoll_options[$lang] : $options = $node->advpoll_options['und'];
    }
    (isset($node->advpoll_choice[$lang])) ? $data['choices'] = $node->advpoll_choice[$lang] : $data['choices'] = $node->advpoll_choice['und'];
    if ($node->advpoll_dates) {
      (isset($node->advpoll_dates[$lang])) ? $data['start_date'] = strtotime($node->advpoll_dates[$lang][0]['value']) : $data['start_date'] = strtotime($node->advpoll_dates['und'][0]['value']);
      (isset($node->advpoll_dates[$lang])) ? $data['end_date'] = strtotime($node->advpoll_dates[$lang][0]['value2']) : $data['end_date'] = strtotime($node->advpoll_dates['und'][0]['value2']);
    } else {
      $data['start_date'] = 0;
      $data['end_date'] = 0;
    }
    (isset($node->advpoll_mode[$lang])) ? $data['mode'] = $node->advpoll_mode[$lang][0]['value'] : $data['mode'] = $node->advpoll_mode['und'][0]['value'];
    (isset($node->advpoll_cookie_duration[$lang])) ? $data['cookie_duration'] = $node->advpoll_cookie_duration[$lang][0]['value'] : $data['cookie_duration'] = $node->advpoll_cookie_duration['und'][0]['value'];
    (isset($node->advpoll_closed[$lang])) ? $data['state'] = $node->advpoll_closed[$lang][0]['value'] : $data['state'] = $node->advpoll_closed['und'][0]['value'];
    (isset($node->advpoll_behavior[$lang])) ? $data['behavior'] = $node->advpoll_behavior[$lang][0]['value'] : $data['behavior'] = $node->advpoll_behavior['und'][0]['value'];
    (isset($node->advpoll_max_choices[$lang])) ? $data['max_choices'] = $node->advpoll_max_choices[$lang][0]['value'] : $data['max_choices'] = $node->advpoll_max_choices['und'][0]['value'];
    (isset($node->advpoll_results[$lang])) ? $data['show_results'] = $node->advpoll_results[$lang][0]['value'] : $data['show_results'] = $node->advpoll_results['und'][0]['value'];
    $data['electoral'] = advpoll_has_data($options, 'electoral');
    $data['write_in'] = advpoll_has_data($options, 'writein');
    $data['block'] = advpoll_has_data($options, 'block');
  }

  return (object) $data;
}