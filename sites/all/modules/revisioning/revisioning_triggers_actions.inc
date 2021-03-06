<?php
// $Id: revisioning_triggers_actions.inc,v 1.8 2009/06/01 03:37:33 rdeboer Exp $

/**
 * @file
 *  Triggers and actions supported by the revisioning module.
 */

/**
 * Implementation of hook_hook_info().
 * Defines triggers available in this module.
 */
function revisioning_hook_info() {
  return array(
    // First key is name of tab on admin/build/trigger page that triggers appear on
    'revisioning' => array(
      'revisioning' => array( // trigger name must equal module name
        // List of trigger operations
        'publish' => array(
          'runs when' => t('When publishing a pending revision'),
        ),
        'revert' => array(
          'runs when' => t('When reverting to an archived revision'),
        ),
        'unpublish' => array(
          'runs when' => t('When unpublishing the current revision'),
        ),
      ),
    ),
  );
}

/**
 * Implementation of hook_<trigger_name>().
 *
 * Note confusing name due to fact that trigger name needs to equal module name.
 * @see revisioning_hook_info()
 *
 * @param $op
 *  trigger operation name
 */
function revisioning_revisioning($op) {
  if (!module_exists("trigger")) {
    return;
  }
  $aids = _trigger_get_hook_aids('revisioning', $op);
  if (empty($aids)) {
    return;
  }
  watchdog('revisioning', '%op trigger is actioning "@aids"', array('%op' => $op, '@aids' => implode(', ', array_keys($aids))));
  global $user;
  $context = array('hook' => 'revisioning', 'op' => $op, 'user' => $user);
  foreach ($aids as $aid => $action_info) {
    if ($action_info['type'] == 'node') {
      if ((arg(0) == 'node') && is_numeric(arg(1))) {
        $object = node_load(array('nid' => arg(1)));
      }
    }
    else {
      $object = $user;
    }
    actions_do($aid, $object, $context);
  }
}

/**
 * Implementation of hook_action_info().
 * Defines actions available in this module.
 */
function revisioning_action_info() {
  return array(
    'revisioning_publish_latest_revision_action' => array(
      'type' => 'node',
      'description' => t('Publish the most recent pending revision'),
      'configurable' => FALSE,
      'hooks' => array(
        'nodeapi' => array('presave'),
      ),
   // Don't need 'changes_node_property'; it will generate a superfluous "save
   // post" action; we're alreay making sure db is updated
   // 'behavior' => array('changes_node_property')
    )
  );
}

/**
 * Implementation of publish_latest_revision action
 */
function revisioning_publish_latest_revision_action(&$node, $context = array()) {
  $type = node_get_types('name', $node->type);
  watchdog('revisioning',
    'Executing publish_latest_revision action for @type %title', array('@type' => $type, '%title' => $node->title),
    WATCHDOG_NOTICE, l(t('view'), "node/$node->nid"));
  revisioning_publish_latest_revision($node);
}
