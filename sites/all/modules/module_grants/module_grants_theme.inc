<?php
// $Id: module_grants_theme.inc,v 1.8 2009/07/03 06:37:27 rdeboer Exp $
/**
 * @file
 *  Include file for module_grants.module, dealing with all theming aspects.
 */

/**
 * Implementation of hook_theme().
 * 
 * Register the theme_hooks() available in this module, with their arguments
 * and default values.
 */
function module_grants_theme() {
  return array(
    'nodes_summary' => array(
       'arguments' => array('nodes' => NULL) // theme_nodes_summary($nodes)
    )
  );
}

/**
 * Theme the passed-in nodes as a table.
 * 
 * Uses the following subthemes:
 * o 'table_nodes', falling back to theme.inc/theme_table() if not defined
 * o 'username', i.e. theme.inc/theme_username()
 *
 * @param $nodes
 *   Array of nodes to display.
 * @return
 *   Themed table HTML or a paragraph saying 'No content found.' if the supplied
 *   array is empty.
 *   
 * @ingroup themeable
 */
function theme_nodes_summary($nodes) {
  $css_path = drupal_get_path('module', 'module_grants') .'/module_grants.css';
  drupal_add_css($css_path, 'module', 'all', FALSE); // also loads /module_grants-rtl.css
  if (!empty($nodes)) {
    // Note the specification of fields doesn't seem to work properly
    // See theme.inc/theme_table(), which uses tablesort.inc/tablesort_header()
    $header = array(
      array('data' => t('Title'), 'field' => 'r.title'),
      array('data' => t('Type'), 'field' => 'n.type'),
      array('data' => t('Creator'), 'field' => 'n.uid'),
      array('data' => t('Last updated'), 'field' => 'timestamp', 'sort' => 'desc'),
      array('data' => t('By'), 'field' => 'r.uid'),
      array('data' => t('Published?'), 'field' => 'status')
    );
    $show_taxonomy_terms = module_exists('taxonomy');
    $show_workflow_state = module_exists('workflow');
    if ($show_taxonomy_terms) {
      $header[] = array('data' => t('Term'), 'field' => 'term');
    }
    if ($show_workflow_state) {
      $header[] = array('data' => t('Workflow state'), 'field' => 'ws.state');
    }
    $rows = array();
    foreach ($nodes as $node) {
      $page_link = user_access('view revisions') && get_number_of_revisions($node->nid) > 1 ? "$node->nid/revisions" : $node->nid;
      $row = array(
        l($node->title, "node/$page_link"),
        check_plain(node_get_types('name', $node)),
        theme('username', user_load(array('uid' => $node->creator_uid))),
        format_date($node->timestamp),
        theme('username', user_load(array('uid' => $node->uid))),
        $node->status ? t('Yes') : t('No')
      );
      if ($show_taxonomy_terms) {
        $row[] = empty($node->term) ? '' : check_plain($node->term);
      }
      if ($show_workflow_state) {
        $row[] = empty($node->state) ? t('No state') : check_plain($node->state);
      }
      $rows[] = $row;
    }
    $attributes = array('class' => 'table-nodes');
    return theme(array('table_nodes', 'table'), $header, $rows, $attributes, $caption = NULL);
  }
  return '<p>'. t('No content found.') .'</p>';
}

/**
 * Implement (in your own module) the function below if you want to override
 * the default way in which the nodes summary table is displayed.
 * If you do, don't forget to register this theme_hook() via <your_module>_theme()
 * in a manner similar to module_grants_theme() in this file.
 * 
 * @param $header
 * @param $rows
 * @return themed HTML, see for instance /includes/theme.inc/theme_table()
 *
 * @ingroup themeable
 * 
function theme_table_nodes($header, $rows) {
}
 */