<?php
/**
 * @file
 * Utility functions for Scopus
 */

/**
 * Find the SCOPUS ID using an other id like DOI, PMID, etc
 *
 * @param string $type
 *   The type of id to use (doi).
 * @param $code
 *   The value of the code to search for.
 *
 * @return mixed
 *   Return the Scopus ID or FALSE.
 */
function islandora_scopus_get_id($type, $code) {
  $api_key = variable_get('islandora_scopus_api_key', '');

  switch (strtolower($type)) {
    case "doi":
      $query = "DOI%28" . urlencode($code) . "%29";
      break;

  }

  $query_url = "http://api.elsevier.com/content/search/scopus?query={$query}";
  $headers = array('Accept' => 'application/json', 'X-ELS-APIKey' => $api_key);
  $response = drupal_http_request($query_url, array('headers' => $headers));
  if ($response->code == 200) {
    $json = json_decode($response->data);
    if ($json->{'search-results'}->{'opensearch:totalResults'} > 0) {
      $entry = reset($json->{'search-results'}->{'entry'});
      if (isset($entry->{'dc:identifier'})) {
        // Scopus ID is "SCOPUS:XXXXX".
        $scopus_id = explode(':', $entry->{'dc:identifier'});
        return $scopus_id[1];
      }
    }
  }
  return FALSE;
}
