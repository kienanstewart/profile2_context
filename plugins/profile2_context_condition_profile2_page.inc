<?php

/**
 * @file
 *
 * Context condition for profile2.
 */

/**
 * Expose profile2 pages as a context condition.
 */
class profile2_context_condition_profile2_page extends context_condition {

  /**
   * Condition values.
   */
  function condition_values() {
    $values = array();
    foreach (profile2_get_types() as $type) {
      $values[check_plain($type->type)] = $type->getTranslation('label');
    }
    return $values;
  }

  /**
   * Options form. Additional conditions for the context.
   */
  function options_form($context) {
    $defaults = $this->fetch_from_context($context, 'options');
    return array(
      'profile2_mode' => array(
        '#title' => t('Mode of profile'),
        '#type' => 'checkboxes',
        '#options' => array(
          'view' => t('View'),
          'register' => t('Register'),
          'edit' => t('Edit')
        ),
        '#description' => t('Set this context on profile2 view/edit modes'),
        '#default_value' => isset($defaults['profile2_mode']) ? $defaults['profile2_mode'] : TRUE,
      ),
    );
  }

  /**
   * Plugin execution.
   */
  public function execute($profile2, $op) {
    foreach ($this->get_contexts($profile2->type) as $context) {
      $options = $this->fetch_from_context($context, 'options');

      if ($selected = $options['profile2_mode'][$op]) {
        $this->condition_met($context, $profile2->type);
      }

    }
  }
}
