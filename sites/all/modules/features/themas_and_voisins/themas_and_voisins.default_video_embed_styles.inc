<?php
/**
 * @file
 * themas_and_voisins.default_video_embed_styles.inc
 */

/**
 * Implements hook_default_video_embed_styles().
 */
function themas_and_voisins_default_video_embed_styles() {
  $export = array();

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'Stream Thématique';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '340px',
      'height' => '249px',
      'theme' => 'dark',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 0,
      'modestbranding' => 1,
      'iv_load_policy' => '3',
      'autohide' => '1',
    ),
    'vimeo' => array(
      'width' => '340px',
      'height' => '249px',
      'color' => 'ffffff',
      'portrait' => 0,
      'title' => 0,
      'byline' => 0,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-vimeo',
  );
  $export['Stream Thématique'] = $video_embed_style;

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'voisin';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '680px',
      'height' => '498px',
      'theme' => 'light',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 0,
      'modestbranding' => 0,
      'iv_load_policy' => '3',
      'autohide' => '2',
    ),
    'vimeo' => array(
      'width' => '680px',
      'height' => '498px',
      'color' => 'ffffff',
      'portrait' => 0,
      'title' => 0,
      'byline' => 0,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-vimeo',
  );
  $export['voisin'] = $video_embed_style;

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'voisin_1';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '680px',
      'height' => '498px',
      'theme' => 'light',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 0,
      'modestbranding' => 0,
      'iv_load_policy' => '3',
      'autohide' => '2',
    ),
    'vimeo' => array(
      'width' => '340px',
      'height' => '248px',
      'color' => 'ffffff',
      'portrait' => 0,
      'title' => 0,
      'byline' => 0,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-vimeo',
  );
  $export['voisin_1'] = $video_embed_style;

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'voisin_2';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '680px',
      'height' => '498px',
      'theme' => 'light',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 0,
      'modestbranding' => 0,
      'iv_load_policy' => '3',
      'autohide' => '2',
    ),
    'vimeo' => array(
      'width' => '380px',
      'height' => '498px',
      'color' => 'ffffff',
      'portrait' => 0,
      'title' => 0,
      'byline' => 0,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-vimeo',
  );
  $export['voisin_2'] = $video_embed_style;

  $video_embed_style = new stdClass();
  $video_embed_style->disabled = FALSE; /* Edit this to true to make a default video_embed_style disabled initially */
  $video_embed_style->api_version = 1;
  $video_embed_style->name = 'voisin_3';
  $video_embed_style->data = array(
    'youtube' => array(
      'width' => '680px',
      'height' => '498px',
      'theme' => 'light',
      'autoplay' => 0,
      'hd' => 1,
      'rel' => 0,
      'showinfo' => 0,
      'modestbranding' => 0,
      'iv_load_policy' => '3',
      'autohide' => '2',
    ),
    'vimeo' => array(
      'width' => '1020px',
      'height' => '746px',
      'color' => 'ffffff',
      'portrait' => 0,
      'title' => 0,
      'byline' => 0,
      'autoplay' => 0,
      'loop' => 0,
    ),
    'data__active_tab' => 'edit-data-vimeo',
  );
  $export['voisin_3'] = $video_embed_style;

  return $export;
}
